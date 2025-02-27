/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:30:47 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 18:08:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	Move the selected object in the scene
*/
void	move_object(t_scene *scene, double x, double y, double z)
{
	int	i;

	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected)
		{
			scene->shapes[i].transform = multiply_matrices(
					scene->shapes[i].transform, translation_matrix(x, y, z));
			update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			scene->needs_render = 1;
			return ;
		}
		i++;
	}
}

/*
**	Scale the selected object in the scene
*/
void	scale_object(t_scene *scene, double scale_factor)
{
	int		i;
	t_tuple	new_scale;

	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected)
		{
			new_scale = multiply_tuple_scalar(
					scene->shapes[i].scale, scale_factor);
			if (new_scale.x >= 0.1 && new_scale.y >= 0.1
				&& new_scale.z >= 0.1 && new_scale.x <= 8
				&& new_scale.y <= 8 && new_scale.z <= 8)
			{
				scene->shapes[i].scale = new_scale;
				scene->shapes[i].transform = multiply_matrices(
						scene->shapes[i].transform, scaling_matrix(
							scale_factor, scale_factor, scale_factor));
				update_matrices(&scene->shapes[i], scene->shapes[i].transform);
				scene->needs_render = 1;
			}
			return ;
		}
		i++;
	}
}

/*
**	Rotate the selected object in the scene.
**	If flag is 1, rotate around Z axis,
**	if 2 - around Y, if 3 - around X
**	We don't rotate spheres
*/
void	rotate_object(t_scene *scene, double angle, int flag)
{
	int	i;

	i = 0;
	while (i < scene->shape_count)
	{
		if (scene->shapes[i].selected && scene->shapes[i].type != SHAPE_SPHERE)
		{
			if (flag == 1)
				scene->shapes[i].transform = multiply_matrices(
						scene->shapes[i].transform, rotation_z_matrix(angle));
			if (flag == 2)
				scene->shapes[i].transform = multiply_matrices(
						rotation_y_matrix(angle), scene->shapes[i].transform);
			if (flag == 3)
				scene->shapes[i].transform = multiply_matrices(
						rotation_z_matrix(angle), scene->shapes[i].transform);
			update_matrices(&scene->shapes[i], scene->shapes[i].transform);
			scene->needs_render = 1;
			return ;
		}
		i++;
	}
}

/*
**	Listens to the keyboard and moves the camera accordingly
**	Handles the movement of the objects in the scene
*/
void	handle_object_movement(t_scene *scene)
{
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
}

/*
**	Listens to the keyboard and moves the camera accordingly
**	Handles the transformation of the objects in the scene
*/
void	handle_object_transformation(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_ADD))
		scale_object(scene, SCALE_UP);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_KP_SUBTRACT))
		scale_object(scene, SCALE_DOWN);
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
