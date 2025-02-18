/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/18 18:28:13 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	return (rotation_matrix);
}

t_matrix	get_transform_matrix(t_shape *shape)
{
	t_tuple	y_axis;
	t_tuple	rot_axis;
	double	rot_angle;	
	double	len;

	len = magnitude(shape->normalized_3d_vector);
	if (len < EPSILON)
		return (identity_matrix(4));
	ft_bzero(&y_axis, sizeof(t_tuple));
	y_axis.y = 1;
	y_axis = normalize(y_axis);
	shape->normalized_3d_vector = normalize(shape->normalized_3d_vector);
	rot_axis = cross(y_axis, shape->normalized_3d_vector);
	rot_axis = normalize(rot_axis);
	rot_angle = acos(dot(y_axis, shape->normalized_3d_vector));
	return(rotation_matrix_sub(rot_axis, rot_angle));
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
			scene->shapes[i]->transform = get_transform_matrix(scene->shapes[i]);
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
	sphere->center = point(0, 5.0, -10.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix(4);
	sphere->material = material(create_color(1.0, 0.8, 0.0), scene.ambient_lightning.ambient, 0.3, 1.0, 300.0, PATTERN_NONE);
	/* sphere->material.reflective = 0.9;
	sphere->material.transparency = 0.0;
	sphere->material.refractive_index = 1.0; */
	scene.shapes[0] = sphere;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, 0, 0);
	floor->normalized_3d_vector = vector(0, 1, 0);
	floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = checker_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	/* floor->material.reflective = 0.2;
	floor->material.transparency = 0.0;
	floor->material.refractive_index = 1.0; */
	scene.shapes[1] = floor;

	t_shape *floor1 = (t_shape *)calloc(1, sizeof(t_shape));
	floor1->type = SHAPE_PLANE;
	floor1->center = point(0, 0, 0);
	floor1->normalized_3d_vector = vector(0, 1, 0);
	floor1->transform = translation_matrix(0, 12.0, 20.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor1->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor1->material.pattern = checker_pattern(create_color(255.0/255.0, 0.0/255.0, 0.0/255.0), create_color(255.0/255.0, 255.0/255.0, 255.0/255.0));
	floor1->material.pattern.transform = scaling_matrix(10, 10, 10);
	/* floor1->material.reflective = 0.2;
	floor1->material.transparency = 0.0;
	floor1->material.refractive_index = 1.0; */
	scene.shapes[2] = floor1;

	scene.camera = init_camera(0.0, 6.0, 20.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(-15.0, 5.0, 5.0), create_color(1.0, 1.0, 1.0), 0.9);

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
