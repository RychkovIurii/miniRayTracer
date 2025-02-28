/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 17:41:26 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_file_ext(t_rt *rt)
{
	const char	*filename;
	const char	*dot;

	filename = rt->filename;
	dot = ft_strrchr(filename, '.');
	if(!dot)
		return(1);
	if (ft_strncmp(dot, ".rt\0", 4))
		return (1);
	return (0);
}

void free_pixels(t_tuple **pixels, int height)
{
	if (!pixels)
		return;
	for (int i = 0; i < height; i++)
	{
		free(pixels[i]);
	}
	free(pixels);
}

int main(int argc, char **argv)
{
	t_rt	*rt;
	
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return(EXIT_FAILURE);
	}
	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
	{
		printf("Could not allocate memory for rt\n");
		return(EXIT_FAILURE);
	}
	initialize_structs(argv, rt);
	if (parse_file(rt))
	{
		free_rt(rt);
		printf("Parsing error\n");
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
	// Gotta error check this stuff
	if (!(rt->scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		free_pixels(rt->scene->pixels, HEIGHT);
		return(EXIT_FAILURE);
	}
	if (!(rt->scene->image = mlx_new_image(rt->scene->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		free_pixels(rt->scene->pixels, HEIGHT);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(rt->scene->mlx, rt->scene->image, 0, 0) == -1)
	{
		mlx_close_window(rt->scene->mlx);
		puts(mlx_strerror(mlx_errno));
		free_pixels(rt->scene->pixels, HEIGHT);
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(rt->scene->mlx, ft_hook, rt->scene);

	mlx_loop(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	free_pixels(rt->scene->pixels, HEIGHT);
	free_rt(rt);
	return (EXIT_SUCCESS);
}
