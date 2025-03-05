/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/05 15:03:57 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_all(char **argv, t_rt *rt)
{
	initialize_structs(argv, rt);
	if (parse_file(rt))
	{
		free_rt(rt);
		ft_putendl_fd("Parsing error", 2);
		exit(1);
	}
	rt->scene->camera = init_camera(
			rt->scene->camera.view_point,
			rt->scene->camera.normal,
			rt->scene->camera.field_of_view);
	if (init_scene_pixels(rt->scene, HEIGHT, WIDTH))
	{
		free_rt(rt);
		exit(error("Failed to initialize scene pixels", 1));
	}
	rt->scene->light = init_light(
			rt->scene->light.position,
			rt->scene->light.color,
			rt->scene->light.brightness);
	set_matrices(rt->scene);
}

void	mlx_all(t_rt *rt)
{
	rt->scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!rt->scene->mlx)
		exit(free_pixels_and_rt(rt, 1, "Error\nFailed to initialize mlx"));
	rt->scene->image = mlx_new_image(rt->scene->mlx, WIDTH, HEIGHT);
	if (!rt->scene->image)
	{
		mlx_close_window(rt->scene->mlx);
		exit(free_pixels_and_rt(rt, 1, "Error\nFailed to create image"));
	}
	if (mlx_image_to_window(rt->scene->mlx, rt->scene->image, 0, 0) == -1)
	{
		mlx_close_window(rt->scene->mlx);
		exit(free_pixels_and_rt(rt, 1, "Error\nFailed to put image to window"));
	}
}

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
		return (error("Invalid number of arguments", 1));
	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		return (error("Could not allocate memory for rt", 1));
	init_all(argv, rt);
	mlx_all(rt);
	mlx_loop_hook(rt->scene->mlx, ft_hook, rt->scene);
	mlx_resize_hook(rt->scene->mlx, &resize_window, rt->scene);
	mlx_loop(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	return (free_pixels_and_rt(rt, 0, NULL));
}
