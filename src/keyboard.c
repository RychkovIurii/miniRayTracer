/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:04:37 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/26 16:36:08 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void handle_mouse_and_exit(t_scene *scene)
{
	int i;
	t_ray ray;
	t_intersects xs;
	t_intersection *closest;

	i = 0;
	if (mlx_is_mouse_down(scene->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		ray = ray_for_pixel(scene->camera, scene->mouse_x, scene->mouse_y, multiply_matrix_by_tuple(scene->camera.transform_inv, point(0, 0, 0)));
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

void move_camera(t_scene *scene, t_tuple point, double angle)
{
	if (angle != 0)
	{
		scene->camera.transform = multiply_matrices(rotation_y_matrix(angle), scene->camera.transform);
		scene->needs_render = 1;
		return ;
	}
	scene->camera.transform = multiply_matrices(scene->camera.transform, translation_matrix(point.x, point.y, point.z));
	scene->needs_render = 1;
}

void handle_camera_movement(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
		move_camera(scene, point(0, -MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
		move_camera(scene, point(0, MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		move_camera(scene, point(-MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		move_camera(scene, point(MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_A))
		move_camera(scene, point(0, 0, 0), -ROTATE_CAMERA_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
		move_camera(scene, point(0, 0, 0), ROTATE_CAMERA_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_W))
		move_camera(scene, point(0, 0, MOVE_STEP), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S))
		move_camera(scene, point(0, 0, -MOVE_STEP), 0);
}

void move_object(t_scene *scene, double x, double y, double z)
{
	int i;
	
	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected)
		{
			scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, translation_matrix(x, y, z));
			update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			scene->needs_render = 1;
			return ;
		}
		i++;
	}
}

void scale_object(t_scene *scene, double scale_factor)
{
	int i;
	t_tuple new_scale;
	
	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected)
		{
			new_scale = multiply_tuple_scalar(scene->shapes[i].scale, scale_factor);
			if (new_scale.x >= 0.1 && new_scale.y >= 0.1 && new_scale.z >= 0.1 && new_scale.x <= 8 && new_scale.y <= 8 && new_scale.z <= 8)
			{
				scene->shapes[i].scale = new_scale;
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, scaling_matrix(scale_factor, scale_factor, scale_factor));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
				scene->needs_render = 1;
			}
			return ;
		}
		i++;
	}
}


void rotate_object(t_scene *scene, double angle, int flag)
{
	int i;
	
	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected && scene->shapes[i].type != SHAPE_SPHERE)
		{
			if (flag == 1)
				scene->shapes[i].transform = multiply_matrices(scene->shapes[i].transform, rotation_z_matrix(angle));
			if (flag == 2)
				scene->shapes[i].transform = multiply_matrices(rotation_y_matrix(angle), scene->shapes[i].transform);
			if (flag == 3)
				scene->shapes[i].transform = multiply_matrices(rotation_z_matrix(angle), scene->shapes[i].transform);
			update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			scene->needs_render = 1;
			return ;
		}
		i++;
	}
}

void handle_object_transformation(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_ADD))
		scale_object(scene, SCALE_UP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_SUBTRACT))
		scale_object(scene, SCALE_DOWN);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_5))
		move_object(scene, 0, 0, MOVE_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_8))
		move_object(scene, 0, 0, -MOVE_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_6))
		move_object(scene, -MOVE_STEP, 0, 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_4))
		move_object(scene, MOVE_STEP, 0, 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_0))
		move_object(scene, 0, -MOVE_STEP, 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_1))
		move_object(scene, 0, MOVE_STEP, 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_7))
		rotate_object(scene, ROTATE_OBJECT_STEP, 1);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_9))
		rotate_object(scene, -ROTATE_OBJECT_STEP, 1);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_EQUAL))
		rotate_object(scene, ROTATE_OBJECT_STEP, 2);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_DIVIDE))
		rotate_object(scene, -ROTATE_OBJECT_STEP, 2);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_2))
		rotate_object(scene, ROTATE_OBJECT_STEP, 3);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_3))
		rotate_object(scene, -ROTATE_OBJECT_STEP, 3);
}

void update_light(t_scene *scene, t_tuple new_vector, double brightness)
{
	if (brightness != 0)
	{
		double new_brightness = scene->light.brightness + brightness;
		if (new_brightness <= 1.0 && new_brightness >= 0.2)
		{
			scene->light.brightness = new_brightness;
			scene->light.intensity = multiply_tuple_scalar(scene->light.color, scene->light.brightness);
			scene->needs_render = 1;
			return ;
		}
	}
	scene->light.position = add_tuple(scene->light.position, new_vector);
	scene->needs_render = 1;
}

void handle_light_controls(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_SHIFT))
		update_light(scene, vector(0, 0, 0), BRIGHTNESS_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT_CONTROL))
		update_light(scene, vector(0, 0, 0), -BRIGHTNESS_STEP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_HOME))
		update_light(scene, vector(0, MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_END))
		update_light(scene, vector(0, -MOVE_STEP, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_PAGE_DOWN))
		update_light(scene, vector(-MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DELETE))
		update_light(scene, vector(MOVE_STEP, 0, 0), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_SHIFT))
		update_light(scene, vector(0, 0, -MOVE_STEP), 0);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_CONTROL))
		update_light(scene, vector(0, 0, MOVE_STEP), 0);
}

void ft_hook(void* param)
{
	t_scene *scene = (t_scene *)param;

	mlx_get_mouse_pos(scene->mlx, &scene->mouse_x, &scene->mouse_y);
	handle_mouse_and_exit(scene);
	handle_camera_movement(scene);
	handle_object_transformation(scene);
	handle_light_controls(scene);

	if (scene->needs_render)
	{
		scene->camera.transform_inv = inverse_matrix(scene->camera.transform);
		ft_render_scene(scene);
		scene->needs_render = 0;
	}
}
