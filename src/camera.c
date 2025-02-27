/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:13:21 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 18:26:14 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_matrix	orientation;

	forward = normalize(substract_tuple(to, from));
	if (fabs(dot(forward, up)) >= (1.0 - EPSILON))
	{
		if (fabs(forward.y) >= (1.0 - EPSILON))
			up = vector(1, 0, 0);
		else
			up = vector(0, 1, 0);
	}
	t_tuple left = cross(forward, normalize(up));
	t_tuple true_up = cross(left, forward);

	
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

	t_matrix translation = translation_matrix(-from.x, -from.y, -from.z);
	return (multiply_matrices(orientation, translation));
}

t_camera init_camera(t_tuple from, t_tuple forward, double fov)
{
	t_camera	camera;
	double		half_view;
	double		aspect;

	camera.hsize = WIDTH;
	camera.vsize = HEIGHT;
	camera.field_of_view = fov;
	half_view = tan(camera.field_of_view * (M_PI / 180.0) * 0.5);
	aspect = (double)camera.hsize / (double)camera.vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / camera.hsize;
	camera.transform = view_transform(from, add_tuple(from, forward), vector(0.0, 1.0, 0.0));
	camera.transform_inv = inverse_matrix(camera.transform);
	return (camera);
}
