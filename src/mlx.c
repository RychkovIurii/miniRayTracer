/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/04 15:26:10 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

/*
**	Resizes the window
**	Resizes the image
**	Initializes the pixels
**	Recalculates the camera parameters
**	Triggers the render
*/
void	resize_window(int width, int height, void *param)
{
	double	aspect;
	double	half_view;
	t_scene	*scene;

	scene = param;
	mlx_resize_image(scene->image, width, height);
	free_pixels(scene->pixels, scene->height);
	scene->pixels = NULL;
	if (init_scene_pixels(scene, height, width))
		exit_and_cleanup(scene->rt);
	half_view = tan(scene->camera.field_of_view * (M_PI / 180.0) * 0.5);
	aspect = (double)width / (double)height;
	if (aspect >= 1)
	{
		scene->camera.half_width = half_view;
		scene->camera.half_height = half_view / aspect;
	}
	else
	{
		scene->camera.half_width = half_view * aspect;
		scene->camera.half_height = half_view;
	}
	scene->camera.pixel_size = (scene->camera.half_width * 2) / width;
	scene->needs_render = 1;
}
