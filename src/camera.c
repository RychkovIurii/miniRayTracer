/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:13:21 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 17:00:30 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** This function creates a view transformation matrix.
** It takes 3 arguments: from, up and forward.
** From is the position of the camera.
** Up is the vector that points upwards.
** Forward is the vector that points towards the camera's target.
** The function calculates the left vector by taking the cross product
** of forward and up.
** @return the view transformation matrix.
*/
static t_matrix	view_transform(t_tuple from, t_tuple up, t_tuple forward)
{
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;
	t_matrix	translation;

	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	ft_bzero(&orientation, sizeof(t_matrix));
	orientation.matrix[0][0] = -left.x;
	orientation.matrix[0][1] = -left.y;
	orientation.matrix[0][2] = -left.z;
	orientation.matrix[1][0] = true_up.x;
	orientation.matrix[1][1] = true_up.y;
	orientation.matrix[1][2] = true_up.z;
	orientation.matrix[2][0] = -forward.x;
	orientation.matrix[2][1] = -forward.y;
	orientation.matrix[2][2] = -forward.z;
	orientation.matrix[3][3] = 1;
	translation = translation_matrix(-from.x, -from.y, -from.z);
	return (multiply_matrices(orientation, translation));
}

/*
** This function calculates the size of the camera.
** It takes a pointer to a camera as an argument.
** It calculates the half width and half height of the camera.
** It also calculates the size of a pixel.
*/
static void	set_camera_size(t_camera *camera)
{
	double	aspect;
	double	half_view;

	half_view = tan(camera->field_of_view * (M_PI / 180.0) * 0.5);
	aspect = (double)WIDTH / (double)HEIGHT;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / WIDTH;
}

/*
** This function initializes a camera.
** It takes 3 arguments: from, forward and fov.
** From is the position of the camera.
** Forward is the vector that points towards the camera's target.
** Fov is the field of view of the camera.
** The function calculates the size of the camera.
** It then calculates the view transformation matrix.
** It then calculates the inverse of the view transformation matrix.
** @return the camera.
*/
t_camera	init_camera(t_tuple from, t_tuple forward, double fov)
{
	t_camera	camera;
	t_tuple		fwd;
	t_tuple		to;
	t_tuple		up;

	camera.field_of_view = fov;
	set_camera_size(&camera);
	to = add_tuple(from, forward);
	up = vector(0.0, 1.0, 0.0);
	fwd = normalize(substract_tuple(to, from));
	if (fabs(dot(fwd, up)) >= (1.0 - EPSILON))
	{
		if (fabs(fwd.y) >= (1.0 - EPSILON))
			up = vector(1, 0, 0);
		else
			up = vector(0, 1, 0);
	}
	camera.transform = view_transform(from, up, fwd);
	camera.transform_inv = inverse_matrix(camera.transform);
	return (camera);
}
