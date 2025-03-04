/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 19:41:54 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt	*rt;
	
	if (argc != 2)
		return (error("Invalid number of arguments", 1));
	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		return (error("Could not allocate memory for rt", 1));
	initialize_structs(argv, rt);
	if (parse_file(rt))
	{
		free_rt(rt);
		ft_putendl_fd("Parsing error", 2);
		return(EXIT_FAILURE);
	}

	rt->scene->camera = init_camera(
		rt->scene->camera.view_point,
		rt->scene->camera.normal,
		rt->scene->camera.field_of_view);

	init_scene_pixels(rt->scene, HEIGHT, WIDTH);
	
	rt->scene->light = init_light(
		rt->scene->light.position,
		rt->scene->light.color,
		rt->scene->light.brightness);

	set_matrices(rt->scene);
	if (!(rt->scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(free_pixels_and_rt(rt, 1));
	}
	if (!(rt->scene->image = mlx_new_image(rt->scene->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		return(free_pixels_and_rt(rt, 1));
	}
	if (mlx_image_to_window(rt->scene->mlx, rt->scene->image, 0, 0) == -1)
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		return(free_pixels_and_rt(rt, 1));
	}
	
	mlx_loop_hook(rt->scene->mlx, ft_hook, rt->scene);
	mlx_resize_hook(rt->scene->mlx, &resize_window, rt->scene);
	mlx_loop(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	return (free_pixels_and_rt(rt, 0));
}
