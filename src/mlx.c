/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 17:10:48 by irychkov         ###   ########.fr       */
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

/* This function returns the color of the pixel at the given coordinates. */
t_tuple	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		return (canvas->pixels[y][x]);
	}
	return (create_color(0, 0, 0)); // Return black if out of bounds
}

int ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_scene(void* param)
{
	t_scene *scene = (t_scene *)param;
	t_canvas *canvas = render(scene->camera, scene);

	for (int y = 0; y < scene->camera.vsize; ++y)
	{
		for (int x = 0; x < scene->camera.hsize; ++x)
		{
			t_tuple color = pixel_at(canvas, x, y);
			int mlx_color = ft_pixel(
				round_value((int)(color.x * 255), 0, 255),
				round_value((int)(color.y * 255), 0, 255),
				round_value((int)(color.z * 255), 0, 255),
				255
			);
			mlx_put_pixel(scene->image, x, y, mlx_color);
		}
	}

	free_canvas(canvas);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
/* 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, 3, 0));
		scene->camera.inverse_transform = inverse_matrix(scene->camera.transform);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, -3, 0));
		scene->camera.inverse_transform = inverse_matrix(scene->camera.transform);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(-3, 0, 0));
		scene->camera.inverse_transform = inverse_matrix(scene->camera.transform);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(3, 0, 0));
		scene->camera.inverse_transform = inverse_matrix(scene->camera.transform);
	} */
}
