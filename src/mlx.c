/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 18:05:26 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* This function clamps a value to a given range. */
int	round_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_scene(void* param)
{
	t_scene *scene = (t_scene *)param;
	render(scene->camera, scene);

	for (int y = 0; y < scene->camera.vsize; ++y)
	{
		for (int x = 0; x < scene->camera.hsize; ++x)
		{
			t_tuple color = scene->pixels[y][x];
			int mlx_color = ft_pixel(
				round_value((int)(color.x * 255), 0, 255),
				round_value((int)(color.y * 255), 0, 255),
				round_value((int)(color.z * 255), 0, 255),
				255
			);
			mlx_put_pixel(scene->image, x, y, mlx_color);
		}
	}
}

/*
**	Handles the keyboard input
**	Checks if the scene needs to be rendered
*/
void	ft_hook(void* param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	mlx_get_mouse_pos(scene->mlx, &scene->mouse_x, &scene->mouse_y);
	handle_mouse_and_exit(scene);
	handle_camera_movement(scene);
	handle_object_movement(scene);
	handle_object_transformation(scene);
	handle_light_controls(scene);

	if (scene->needs_render)
	{
		scene->camera.transform_inv = inverse_matrix(scene->camera.transform);
		ft_render_scene(scene);
		scene->needs_render = 0;
	}
}
