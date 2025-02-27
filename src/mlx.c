/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:01:55 by irychkov         ###   ########.fr       */
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
