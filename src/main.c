/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/19 16:15:43 by irychkov         ###   ########.fr       */
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
    printf("Pattern: %d\n", material.pattern); // Assuming pattern is an enum or integer
    printf("Pattern: %d\n", material.reflective);
	printf("Pattern: %d\n", material.transparency);
	printf("Pattern: %d\n", material.refractive_index);
	printf("\n");
}


void print_shape(const t_shape *shape)
{
	if (!shape)
		return;

	printf("Shape Type: %d\n", shape->type);
	printf("Center: (%f, %f, %f)\n", shape->center.x, shape->center.y, shape->center.z);
	printf("Radius: %f\n", shape->radius);
	printf("Scale: (%f, %f, %f)\n", shape->scale.x, shape->scale.y, shape->scale.z);
	printf("Normalized Vector: (%f, %f, %f)\n", 
		shape->normalized_3d_vector.x, 
		shape->normalized_3d_vector.y, 
		shape->normalized_3d_vector.z);
	
	print_material(shape->material);
	printf("Transformation Matrix:\n");
	for (int i = 0; i < shape->transform.size; i++)
	{
		for (int j = 0; j < shape->transform.size; j++)
		{
			printf("%f ", shape->transform.matrix[i][j]);
		}
		printf("\n");
	}
}

void print_shapes(t_shape **shapes)
{
	if (!shapes)
		return;

	int i = 0;
	while (shapes[i] != NULL)
	{
		printf("Shape %d:\n", i);
		print_shape(shapes[i]);
		printf("\n");
		i++;
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
	rotation_matrix = create_matrix(4);
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

	len = magnitude(shape->normalized_3d_vector);
	if (len < EPSILON)
		return (identity_matrix(4));
	shape->normalized_3d_vector = normalize(shape->normalized_3d_vector);
	y_axis = vector(0, 1, 0);
	y_axis = normalize(y_axis);
	if (fabs(dot(y_axis, shape->normalized_3d_vector) - 1.0) < EPSILON)
		return (identity_matrix(4));
	rot_axis = cross(y_axis, shape->normalized_3d_vector);
	printf("Cross Product (Rotation Axis): (%f, %f, %f)\n", rot_axis.x, rot_axis.y, rot_axis.z);
	if (magnitude(rot_axis) < EPSILON)
		return (identity_matrix(4));
	rot_axis = normalize(rot_axis);
	rot_angle = acos(fmax(-1.0, fmin(1.0, dot(y_axis, shape->normalized_3d_vector))));
	printf("Rotation Axis: (%f, %f, %f), Angle: %f\n", rot_axis.x, rot_axis.y, rot_axis.z, rot_angle);
	return(rotation_matrix_sub(rot_axis, rot_angle));
}

t_matrix	combine_all_transforms(t_shape *shape)
{
	t_matrix	translation_x_rotation;
	t_matrix	result;

	printf("Before rotation: Normalized Vector: (%f, %f, %f)\n",
       shape->normalized_3d_vector.x, shape->normalized_3d_vector.y, shape->normalized_3d_vector.z);
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
	while (scene->shapes[i] != NULL)
	{
		if (scene->shapes[i]->type == SHAPE_SPHERE)
		{
			scene->shapes[i]->transform = identity_matrix(4);
		}
		else if (scene->shapes[i]->type == SHAPE_PLANE)
		{
			scene->shapes[i]->transform = combine_all_transforms(scene->shapes[i]);
		}
		i++;
	}
}



int main(void)
{
	t_scene scene;

	// Initialize the scene
	scene.shapes = (t_shape **)calloc(4, sizeof(t_shape *));

	scene.ambient_lightning.ambient = 0.2;
	scene.ambient_lightning.color = create_color(255/255.0, 255/255.0, 255/255.0);

	t_shape *sphere = (t_shape *)calloc(1, sizeof(t_shape));
	sphere->type = SHAPE_SPHERE;
	sphere->center = point(0, 6.0, 0.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix(4);
	sphere->material = material(create_color(1.0, 0.8, 0.0), scene.ambient_lightning.ambient, 0.3, 1.0, 300.0, PATTERN_NONE);
	/* sphere->material.reflective = 0.9;
	sphere->material.transparency = 0.0;
	sphere->material.refractive_index = 1.0; */
	scene.shapes[0] = sphere;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, -3.0, 0);
	floor->normalized_3d_vector = vector(0, 1, 0);
	floor->scale = vector(1, 1, 1);
	//floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = checker_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	/* floor->material.reflective = 0.2;
	floor->material.transparency = 0.0;
	floor->material.refractive_index = 1.0; */
	scene.shapes[1] = floor;

	t_shape *wall = (t_shape *)calloc(1, sizeof(t_shape));
	wall->type = SHAPE_PLANE;
	wall->center = point(0, 0, -100);
	wall->normalized_3d_vector = vector(0.4, 0, 1);
	wall->scale = vector(1, 1, 1);
	//wall->transform = translation_matrix(0, 12.0, 20.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	wall->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	wall->material.pattern = checker_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	wall->material.pattern.transform = scaling_matrix(2, 2, 2);
	/* wall->material.reflective = 0.2;
	wall->material.transparency = 0.0;
	wall->material.refractive_index = 1.0; */
	scene.shapes[2] = wall;

	scene.camera = init_camera(0.0, 6.0, -10.0, vector(0.0, 0.0, 1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(0, 5.0, 30.0), create_color(1.0, 1.0, 1.0), 0.9);

	set_matrices(&scene);

	print_shapes(scene.shapes);

	// Gotta error check this stuff
	if (!(scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(scene.image = mlx_new_image(scene.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(scene.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(scene.mlx, scene.image, 0, 0) == -1)
	{
		mlx_close_window(scene.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(scene.mlx, ft_render_scene, &scene);
	mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);

	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	free(scene.shapes[0]);
	free(scene.shapes[1]);
	free(scene.shapes);
	return (EXIT_SUCCESS);
}
