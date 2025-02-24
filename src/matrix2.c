/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:05:20 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/23 15:16:10 by irychkov         ###   ########.fr       */
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
			scene->shapes[i].transform = combine_all_transforms(&scene->shapes[i]);
		}
		else if (scene->shapes[i].type == SHAPE_CYLINDER)
			scene->shapes[i].transform = combine_all_transforms(&scene->shapes[i]);
		i++;
	}
}
