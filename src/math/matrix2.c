/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:05:20 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 13:39:22 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Translation matrix.
** @param x: The x (double) translation.
** @param y: The y (double) translation.
** @param z: The z (double) translation.
** @returns a new translation matrix.
*/
t_matrix	translation_matrix(double x, double y, double z)
{
	t_matrix	result;

	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = 1;
	result.matrix[1][1] = 1;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	result.matrix[0][3] = x;
	result.matrix[1][3] = y;
	result.matrix[2][3] = z;
	return (result);
}

/* Scaling matrix.
** @param x: The x (double) scaling.
** @param y: The y (double) scaling.
** @param z: The z (double) scaling.
** @returns a new scaling matrix.
*/
t_matrix	scaling_matrix(double x, double y, double z)
{
	t_matrix	result;

	if (fabs(x) < EPSILON || fabs(y) < EPSILON || fabs(z) < EPSILON)
		return (identity_matrix());
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = x;
	result.matrix[1][1] = y;
	result.matrix[2][2] = z;
	result.matrix[3][3] = 1;
	return (result);
}

/* Rotation X matrix.
** @param radian (double) : The angle in radians.
** @returns a new rotation matrix.
*/
t_matrix	rotation_x_matrix(double radian)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = 1.0;
	result.matrix[1][1] = cos_r;
	result.matrix[1][2] = -sin_r;
	result.matrix[2][1] = -sin_r;
	result.matrix[2][2] = cos_r;
	result.matrix[3][3] = 1.0;
	return (result);
}

/* Rotation Y matrix.
** @param radian (double) : The angle in radians.
** @returns a new rotation matrix.
*/
t_matrix	rotation_y_matrix(double radian)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = cos_r;
	result.matrix[0][2] = sin_r;
	result.matrix[1][1] = 1.0;
	result.matrix[2][0] = -sin_r;
	result.matrix[2][2] = cos_r;
	result.matrix[3][3] = 1.0;
	return (result);
}

/* Rotation Z matrix.
** @param radian (double) : The angle in radians.
** @returns a new rotation matrix.
*/
t_matrix	rotation_z_matrix(double radian)
{
	t_matrix	result;
	double		cos_r;
	double		sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = cos_r;
	result.matrix[0][1] = -sin_r;
	result.matrix[1][0] = sin_r;
	result.matrix[1][1] = cos_r;
	result.matrix[2][2] = 1.0;
	result.matrix[3][3] = 1.0;
	return (result);
}
