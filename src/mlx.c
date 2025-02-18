/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/18 17:18:11 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
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
	/* if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5; */
}
