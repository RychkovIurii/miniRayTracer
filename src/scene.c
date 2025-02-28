/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:20:58 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 11:21:32 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** This function clamps a value to a given range.
** @param value the value to clamp.
** @param min the minimum value.
** @param max the maximum value.
** @return the clamped value.
*/
int	round_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*
** This function creates a pixel from the given color values.
** @param r the red value.
** @param g the green value.
** @param b the blue value.
** @param a the alpha value.
** @return the pixel.
*/
int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
** This function creates a ray for a given pixel.
** @param camera the camera.
** @param px the x coordinate of the pixel.
** @param py the y coordinate of the pixel.
** @param origin the origin of the ray.
** @return the ray.
*/
t_ray	ray_for_pixel(t_camera camera, int px, int py, t_tuple origin)
{
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	direction;

	world_x = camera.half_width - (px + 0.5) * camera.pixel_size;
	world_y = camera.half_height - (py + 0.5) * camera.pixel_size;
	pixel = multiply_matrix_by_tuple(
			camera.transform_inv, point(world_x, world_y, -1));
	direction = normalize(substract_tuple(pixel, origin));
	return (create_ray(origin, direction));
}

/*
** This function renders the scene.
** @param camera the camera.
** @param scene the scene.
*/
void	render(t_camera camera, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_tuple	origin;

	camera.transform_inv = inverse_matrix(camera.transform);
	origin = multiply_matrix_by_tuple(camera.transform_inv, point(0, 0, 0));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_for_pixel(camera, x, y, origin);
			scene->pixels[y][x] = color_at(scene, ray, DEFAULT_REMAINING);
			x++;
		}
		y++;
	}
}

/*
** This function renders the scene.
** Then it transforms the color values to pixel values.
** And puts the pixels on the screen.
** @param param the scene.
*/
void	ft_render_scene(void *param)
{
	int		y;
	int		x;
	t_scene	*scene;
	t_tuple	color;

	scene = (t_scene *)param;
	y = 0;
	render(scene->camera, scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = scene->pixels[y][x];
			mlx_put_pixel(scene->image, x, y, ft_pixel(
					round_value((int)(color.x * 255), 0, 255),
					round_value((int)(color.y * 255), 0, 255),
					round_value((int)(color.z * 255), 0, 255),
					255));
			x++;
		}
		y++;
	}
}
