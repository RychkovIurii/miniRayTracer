/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:40:07 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 14:34:47 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Function updates the matrices of the shape.
** It sets the transform, transform_inv and transpose_inv matrices of the shape.
** @param shape: The shape to update.
** @param transform: The transform matrix to set.
*/
void	update_matrices(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
	shape->transform_inv = inverse_matrix(shape->transform);
	shape->transpose_inv = transpose_matrix(shape->transform_inv);
}

/* Function creates a rotation matrix around based on the given axis and angle.
** @param r_ax: The axis to rotate around.
** @param r_angle: The angle to rotate.
** @returns the rotation matrix.
*/
t_matrix	rotation_matrix_sub(t_tuple r_ax, double r_angle)
{
	t_matrix	rotation_mx;
	double		cosine;
	double		sine;
	double		one_min_cos;

	cosine = cos(r_angle);
	sine = sin(r_angle);
	one_min_cos = 1 - cosine;
	ft_bzero(&rotation_mx, sizeof(t_matrix));
	rotation_mx.matrix[0][0] = r_ax.x * r_ax.x * one_min_cos + cosine;
	rotation_mx.matrix[0][1] = r_ax.x * r_ax.y * one_min_cos - r_ax.z * sine;
	rotation_mx.matrix[0][2] = r_ax.x * r_ax.z * one_min_cos + r_ax.y * sine;
	rotation_mx.matrix[1][0] = r_ax.x * r_ax.y * one_min_cos + r_ax.z * sine;
	rotation_mx.matrix[1][1] = r_ax.y * r_ax.y * one_min_cos + cosine;
	rotation_mx.matrix[1][2] = r_ax.y * r_ax.z * one_min_cos - r_ax.x * sine;
	rotation_mx.matrix[2][0] = r_ax.x * r_ax.z * one_min_cos - r_ax.y * sine;
	rotation_mx.matrix[2][1] = r_ax.y * r_ax.z * one_min_cos + r_ax.x * sine;
	rotation_mx.matrix[2][2] = r_ax.z * r_ax.z * one_min_cos + cosine;
	rotation_mx.matrix[3][3] = 1;
	return (rotation_mx);
}

/* Function creates a rotation matrix based on the normal of the shape.
** @param shape: The shape to rotate.
** @returns the rotation matrix.
*/
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
	y_axis = normalize(vector(0, 1, 0));
	if (fabs(dot(y_axis, shape->normal) - 1.0) < EPSILON)
		return (identity_matrix());
	rot_axis = cross(y_axis, shape->normal);
	if (magnitude(rot_axis) < EPSILON)
		return (identity_matrix());
	rot_axis = normalize(rot_axis);
	rot_angle = acos(fmax(-1.0, fmin(1.0, dot(y_axis, shape->normal))));
	return (rotation_matrix_sub(rot_axis, rot_angle));
}

/* Function combines all the transformations of the shape.
** @param shape: The shape to combine the transformations.
** @returns the combined transformation matrix.
*/
t_matrix	combine_all_transforms(t_shape *shape)
{
	t_matrix	scaling_x_rotation;
	t_matrix	result;

	scaling_x_rotation = multiply_matrices(
			scaling_matrix(shape->scale.x, shape->scale.y, shape->scale.z),
			get_rotation_matrix(shape));
	result = multiply_matrices(
			translation_matrix(
				shape->center.x, shape->center.y, shape->center.z),
			scaling_x_rotation);
	return (result);
}

/* Function sets the matrices of all the shapes in the scene.
** @param scene: The scene to set the matrices.
*/
void	set_matrices(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].type == SHAPE_SPHERE)
			update_matrices(
				&scene->shapes[i], combine_all_transforms(&scene->shapes[i]));
		else if (scene->shapes[i].type == SHAPE_PLANE)
			update_matrices(
				&scene->shapes[i], combine_all_transforms(&scene->shapes[i]));
		else if (scene->shapes[i].type == SHAPE_CYLINDER)
			update_matrices(
				&scene->shapes[i], combine_all_transforms(&scene->shapes[i]));
		else if (scene->shapes[i].type == SHAPE_CONE)
			update_matrices(
				&scene->shapes[i], combine_all_transforms(&scene->shapes[i]));
		i++;
	}
}
