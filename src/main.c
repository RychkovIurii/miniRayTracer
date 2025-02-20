/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 17:57:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_material(t_material material)
{
    printf("Material:\n");
    printf("Color: (%f, %f, %f)\n", material.color.x, material.color.y, material.color.z);
    printf("Ambient: %f\n", material.ambient);
    printf("Diffuse: %f\n", material.diffuse);
    printf("Specular: %f\n", material.specular);
    printf("Shininess: %f\n", material.shininess);
    printf("has_pattern: %d\n", material.has_pattern); // Assuming pattern is an enum or integer
    printf("reflective: %f\n", material.reflective);
	printf("transparency: %f\n", material.transparency);
	printf("refractive_index: %f\n", material.refractive_index);
	printf("\n");
}


void print_shape(t_shape *shape)
{
	if (!shape)
		return;

	printf("Shape Type: %d\n", shape->type);
	printf("Center: (%f, %f, %f)\n", shape->center.x, shape->center.y, shape->center.z);
	printf("Radius: %f\n", shape->radius);
	printf("Scale: (%f, %f, %f)\n", shape->scale.x, shape->scale.y, shape->scale.z);
	printf("Normalized Vector: (%f, %f, %f)\n", 
		shape->normal.x, 
		shape->normal.y, 
		shape->normal.z);
	
	print_material(shape->material);
	printf("Transformation Matrix:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", shape->transform.matrix[i][j]);
		}
		printf("\n");
	}
}

/* void print_shapes(t_scene *scene)
{
	if (!scene->shapes)
		return;

	int i = 0;
	while (i < scene->shape_count)
	{
		printf("Shape %d:\n", i);
		print_shape(scene->shapes[i]);
		printf("\n");
		i++;
	}
} */

int	validate_file_ext(t_rt *rt)
{
	const char	*filename;
	const char	*dot;

	filename = rt->filename;
	dot = ft_strrchr(filename, '.');
	if(!dot)
		return(1);
	if (ft_strncmp(dot, ".rt\0", 4))
		return (1);
	return (0);
}

void	initialize_structs(char **argv, t_rt *rt)
{
	rt->filename = argv[1];
	if (validate_file_ext(rt))
	{
		printf("Invalid file extension\n");
		free(rt);
		exit(EXIT_FAILURE);
	}
}


t_matrix	rotation_matrix_sub(t_tuple r_ax, double r_angle)
{
	t_matrix	rotation_matrix;
	double	cosine;
	double	sine;
	double	one_min_cos;

	cosine = cos(r_angle);
	sine = sin(r_angle);
	one_min_cos = 1 - cosine;
	ft_bzero(&rotation_matrix, sizeof(t_matrix));
	rotation_matrix.matrix[0][0] = r_ax.x * r_ax.x * one_min_cos + cosine;
	rotation_matrix.matrix[0][1] = r_ax.x * r_ax.y * one_min_cos - r_ax.z * sine;
	rotation_matrix.matrix[0][2] = r_ax.x * r_ax.z * one_min_cos + r_ax.y * sine;
	rotation_matrix.matrix[1][0] = r_ax.x * r_ax.y * one_min_cos + r_ax.z * sine;
	rotation_matrix.matrix[1][1] = r_ax.y * r_ax.y * one_min_cos + cosine;
	rotation_matrix.matrix[1][2] = r_ax.y * r_ax.z * one_min_cos - r_ax.x * sine;
	rotation_matrix.matrix[2][0] = r_ax.x * r_ax.z * one_min_cos - r_ax.y * sine;
	rotation_matrix.matrix[2][1] = r_ax.y * r_ax.z * one_min_cos + r_ax.x * sine;
	rotation_matrix.matrix[2][2] = r_ax.z * r_ax.z * one_min_cos + cosine;
	rotation_matrix.matrix[3][3] = 1;
	printf("Rotation Matrix:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", rotation_matrix.matrix[i][j]);
		printf("\n");
	}
	return (rotation_matrix);
}

t_matrix	get_rotation_matrix(t_shape *shape)
{
	t_tuple	y_axis;
	t_tuple	rot_axis;
	double	rot_angle;	
	double	len;

	len = magnitude(shape->normal);
	if (len < EPSILON)
		return (identity_matrix());
	shape->normal = normalize(shape->normal);
	y_axis = vector(0, 1, 0);
	y_axis = normalize(y_axis);
	if (fabs(dot(y_axis, shape->normal) - 1.0) < EPSILON)
		return (identity_matrix());
	rot_axis = cross(y_axis, shape->normal);
	printf("Cross Product (Rotation Axis): (%f, %f, %f)\n", rot_axis.x, rot_axis.y, rot_axis.z);
	if (magnitude(rot_axis) < EPSILON)
		return (identity_matrix());
	rot_axis = normalize(rot_axis);
	rot_angle = acos(fmax(-1.0, fmin(1.0, dot(y_axis, shape->normal))));
	printf("Rotation Axis: (%f, %f, %f), Angle: %f\n", rot_axis.x, rot_axis.y, rot_axis.z, rot_angle);
	return(rotation_matrix_sub(rot_axis, rot_angle));
}

t_matrix	combine_all_transforms(t_shape *shape)
{
	t_matrix	translation_x_rotation;
	t_matrix	result;

	printf("Before rotation: Normalized Vector: (%f, %f, %f)\n",
       shape->normal.x, shape->normal.y, shape->normal.z);
	translation_x_rotation = multiply_matrices(translation_matrix(shape->center.x, shape->center.y, shape->center.z), get_rotation_matrix(shape));
	result = multiply_matrices(translation_x_rotation, scaling_matrix(shape->scale.x, shape->scale.y, shape->scale.z));
/* 	result = inverse_matrix(result);
	result = transpose_matrix(result); */
	return (result);
}

void	set_matrices(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].type == SHAPE_SPHERE)
		{
			scene->shapes[i].transform = identity_matrix();
		}
		else if (scene->shapes[i].type == SHAPE_PLANE)
		{
			scene->shapes[i].transform = combine_all_transforms(scene->shapes[i]);
		}
		i++;
	}
}



int main(void)

	/* t_scene scene;

	// Initialize the scene
	scene.shapes = (t_shape **)calloc(4, sizeof(t_shape *));

	scene.ambient.ratio = 0.2;
	scene.ambient.color = create_color(255/255.0, 255/255.0, 255/255.0);

	t_shape *sphere = (t_shape *)calloc(1, sizeof(t_shape));
	sphere->type = SHAPE_SPHERE;
	sphere->center = point(0, 6.0, -20.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix();
	sphere->material = material(create_color(1.0, 0.8, 0.0), scene.ambient.ratio, 0.3, 1.0, 300.0, PATTERN_NONE);
	sphere->material.reflective = 0.9;
	sphere->material.transparency = 0.0;
	sphere->material.refractive_index = 1.0;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, -3.0, 0);
	floor->normal = vector(0, 1, 0);
	floor->scale = vector(1, 1, 1);
	//floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient.ratio, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	floor->material.reflective = 0.2;
	floor->material.transparency = 0.0;
	floor->material.refractive_index = 0.0;
	scene.shapes[1] = floor;

	t_shape *wall = (t_shape *)calloc(1, sizeof(t_shape));
	wall->type = SHAPE_PLANE;
	wall->center = point(0, 0, 100);
	wall->normal = vector(0.0, 0, 1);
	wall->scale = vector(1, 1, 1);
	//wall->transform = translation_matrix(0, 12.0, 20.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	wall->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient.ratio, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	wall->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	wall->material.pattern.transform = scaling_matrix(20, 20, 20);
	wall->material.reflective = 0.2;
	wall->material.transparency = 0.0;
	wall->material.refractive_index = 0.0;
	scene.shapes[2] = wall;

	scene.camera = init_camera(0.0, 6.0, 15.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(0, 30.0, 30.0), create_color(1.0, 1.0, 1.0), 0.9);

	set_matrices(&scene);

	print_shapes(scene);

	// Gotta error check this stuff
	
	
	mlx_loop_hook(scene.mlx, ft_render_scene, &scene);
	mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);

	scene.light = init_light(point(-20.0, 1.0, 0.0), create_color(1.0, 1.0, 1.0), 0.7); 
	
	
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	free(scene.shapes[0]);
	free(scene.shapes[1]);
	free(scene.shapes);*/



int32_t main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_rt	*rt;
	
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return(EXIT_FAILURE);
	}
	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		return(EXIT_FAILURE);
	initialize_structs(argv, rt);
	if (parse_file(rt))
		return(EXIT_FAILURE);
	rt->scene->mlx = mlx;
		rt->scene->camera = init_camera(
		rt->scene->camera.view_point.x,
		rt->scene->camera.view_point.y,
		rt->scene->camera.view_point.z,
		rt->scene->camera.normal,
		rt->scene->camera.field_of_view,
		WIDTH, HEIGHT);

	rt->scene->light = init_light(
		rt->scene->light.position,
		rt->scene->light.color,
		rt->scene->light.brightness);

	set_matrices(rt->scene);
	// Gotta error check this stuff
	if (!(rt->scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(rt->scene->image = mlx_new_image(rt->scene->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(rt->scene->mlx, rt->scene->image, 0, 0) == -1)
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(rt->scene->mlx, ft_render_scene, rt->scene);
	mlx_loop_hook(rt->scene->mlx, ft_hook, rt->scene->mlx);

	mlx_loop(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	free_rt(rt);
	return (EXIT_SUCCESS);
}