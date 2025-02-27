/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 19:33:48 by irychkov         ###   ########.fr       */
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

/*
**	Handles the keyboard input
**	Checks if the scene needs to be rendered
*/
void	ft_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
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
