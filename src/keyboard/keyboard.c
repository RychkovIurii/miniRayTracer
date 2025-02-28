/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:04:37 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:58:00 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	Handles keyboard movement and rotation of the objects
**	If angle is 0, moves the camera, otherwise rotates it
*/
void	move_camera(t_scene *scene, t_tuple point, double angle)
{
	if (angle != 0)
	{
		scene->camera.transform = multiply_matrices(
				rotation_y_matrix(angle), scene->camera.transform);
		scene->needs_render = 1;
		return ;
	}
	scene->camera.transform = multiply_matrices(
			scene->camera.transform,
			translation_matrix(point.x, point.y, point.z));
	scene->needs_render = 1;
}

/*
**	Listens to the keyboard and moves the camera accordingly
*/
void	handle_camera_movement(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
		move_camera(scene, point(0, -MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
		move_camera(scene, point(0, MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_A))
		move_camera(scene, point(MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
		move_camera(scene, point(-MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		move_camera(scene, point(0, 0, 0), -ROTATE_CAMERA_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		move_camera(scene, point(0, 0, 0), ROTATE_CAMERA_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_W))
		move_camera(scene, point(0, 0, MOVE_STEP), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S))
		move_camera(scene, point(0, 0, -MOVE_STEP), 0);
}

/*
**	Updates the light position and brightness
**	Also checks if the brightness is within the limits
*/
void	update_light(t_scene *scene, t_tuple new_vector, double brightness)
{
	double	new_brightness;

	if (brightness != 0)
	{
		new_brightness = scene->light.brightness + brightness;
		if (new_brightness <= 1.0 && new_brightness >= 0.2)
		{
			scene->light.brightness = new_brightness;
			scene->light.intensity = multiply_tuple_scalar(
					scene->light.color, scene->light.brightness);
			scene->needs_render = 1;
			return ;
		}
	}
	scene->light.position = add_tuple(scene->light.position, new_vector);
	scene->needs_render = 1;
}

/*
**	Listens to the keyboard and moves the light accordingly
**	Also changes the brightness of the light
*/
void	handle_light_controls(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_SHIFT))
		update_light(scene, vector(0, 0, 0), BRIGHTNESS_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_CONTROL))
		update_light(scene, vector(0, 0, 0), -BRIGHTNESS_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_SHIFT))
		update_light(scene, vector(0, MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_CONTROL))
		update_light(scene, vector(0, -MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DELETE))
		update_light(scene, vector(-MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_PAGE_DOWN))
		update_light(scene, vector(MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_HOME))
		update_light(scene, vector(0, 0, -MOVE_STEP), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_END))
		update_light(scene, vector(0, 0, MOVE_STEP), 0);
}

/*
**	Listens to the keyboard and the mouse.
**	Handles the right mouse button click to select the object
**	Handles the escape key to close the window
*/
void	handle_mouse_and_exit(t_scene *scene)
{
	int				i;
	t_ray			ray;
	t_intersects	xs;
	t_intersection	*closest;

	i = 0;
	if (mlx_is_mouse_down(scene->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		ray = ray_for_pixel(scene->camera, scene->mouse_x, scene->mouse_y,
				multiply_matrix_by_tuple(
					scene->camera.transform_inv, point(0, 0, 0)));
		xs = intersect_scene(scene, ray);
		closest = hit(xs);
		if (closest && closest->object)
		{
			while (i < scene->shape_count)
				scene->shapes[i++].selected = 0;
			closest->object->selected = 1;
		}
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
}
