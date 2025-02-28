/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 11:27:36 by irychkov         ###   ########.fr       */
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
