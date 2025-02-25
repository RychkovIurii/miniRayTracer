/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/25 15:21:12 by irychkov         ###   ########.fr       */
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
/*t_tuple	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		return (canvas->pixels[y][x]);
	}
	return (create_color(0, 0, 0)); // Return black if out of bounds
}
 */
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

void ft_hook(void* param)
{
	t_scene *scene = (t_scene *)param;

	mlx_get_mouse_pos(scene->mlx, &scene->mouse_x, &scene->mouse_y);
	if (mlx_is_mouse_down(scene->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		t_ray ray = ray_for_pixel(scene->camera, scene->mouse_x, scene->mouse_y, multiply_matrix_by_tuple(scene->camera.transform_inv, point(0, 0, 0)));
		t_intersects xs = intersect_scene(scene, ray);
		t_intersection *closest = hit(xs);
		if (closest->object)
		{
			int i = 0;
			while (i < scene->shape_count)
			{
				scene->shapes[i].selected = 0;
				i++;
			}
			closest->object->selected = 1;
		}
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, -0.4, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, 0.4, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(-0.4, 0, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0.4, 0, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_A))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, rotation_y_matrix(0.2));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, rotation_y_matrix(-0.2));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, 0, -0.8));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_W))
	{
		scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(0, 0, 0.8));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_ADD))
	{
		int i;

		i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected == 1)
			{
				t_tuple new_scale = multiply_tuple_scalar(scene->shapes[i].scale, 2);
				
				if (new_scale.x <= 8 && new_scale.y <= 8 && new_scale.z <= 8)
				{
					scene->shapes[i].scale = new_scale;
					scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, scaling_matrix(2, 2, 2));
					update_matrices(&scene->shapes[i], scene->shapes[i].transform);
				}
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_SUBTRACT))
	{
		int i;

		i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected == 1)
			{
				t_tuple new_scale = multiply_tuple_scalar(scene->shapes[i].scale, 0.5);
				
				if (new_scale.x >= 0.1 && new_scale.y >= 0.1 && new_scale.z >= 0.1)
				{
					scene->shapes[i].scale = new_scale;
					scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, scaling_matrix(0.5, 0.5, 0.5));
					update_matrices(&scene->shapes[i], scene->shapes[i].transform);
				}
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_5))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(0, 0, 0.8));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_8))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(0, 0, -0.8));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_6))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(-0.4, 0, 0));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_4))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(0.4, 0, 0));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_0))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(0, -0.4, 0));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_1))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(0, 0.4, 0));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_7))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected && scene->shapes[i].type != SHAPE_SPHERE)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, rotation_z_matrix(0.2));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_9))
	{
		int i = 0;
		while (i < scene->shape_count)
		{
			if (scene->shapes[i].selected && scene->shapes[i].type != SHAPE_SPHERE)
			{
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, rotation_z_matrix(-0.2));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			}
			i++;
		}
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_SHIFT))
	{
		double new_brightness = scene->light.brightness + 0.1;
		if (new_brightness <= 1.0)
		{
			scene->light.brightness = new_brightness;
			scene->light.intensity = multiply_tuple_scalar(scene->light.color, scene->light.brightness);
			scene->needs_render = 1;
		}
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_CONTROL))
	{
		double new_brightness = scene->light.brightness - 0.1;
		if (new_brightness >= 0.2)
		{
			scene->light.brightness = new_brightness;
			scene->light.intensity = multiply_tuple_scalar(scene->light.color, scene->light.brightness);
			scene->needs_render = 1;
		}
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_HOME))
	{
		scene->light.position = add_tuple(scene->light.position, vector(0, 1, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_END))
	{
		scene->light.position = add_tuple(scene->light.position, vector(0, -1, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_PAGE_DOWN))
	{
		scene->light.position = add_tuple(scene->light.position, vector(-1, 0, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DELETE))
	{
		scene->light.position = add_tuple(scene->light.position, vector(1, 0, 0));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_SHIFT))
	{
		scene->light.position = add_tuple(scene->light.position, vector(0, 0, -1));
		scene->needs_render = 1;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_CONTROL))
	{
		scene->light.position = add_tuple(scene->light.position, vector(0, 0, 1));
		scene->needs_render = 1;
	}
	if (scene->needs_render)
	{
		scene->camera.transform_inv = inverse_matrix(scene->camera.transform);
		ft_render_scene(scene);
		scene->needs_render = 0; // Reset flag after rendering
	}
}


// Rotation for cylinders??? Shadows if we rotate.
