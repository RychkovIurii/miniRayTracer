/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:17:37 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/04 15:29:45 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	init_light(t_tuple position, t_tuple color, double brightness)
{
	t_light	light;

	light.position = position;
	light.color = color;
	light.brightness = brightness;
	light.intensity = multiply_tuple_scalar(color, brightness);
	return (light);
}

int	init_scene_pixels(t_scene *scene, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	scene->height = height;
	scene->width = width;
	scene->pixels = malloc(height * sizeof(t_tuple *));
	if (!scene->pixels)
		return (1);
	while (i < height)
	{
		j = 0;
		scene->pixels[i] = malloc(width * sizeof(t_tuple));
		if (!scene->pixels[i])
			return (free_pixels_back(scene->pixels, i));
		while (j < width)
		{
			scene->pixels[i][j] = create_color(0, 0, 0);
			j++;
		}
		i++;
	}
	return (0);
}

static int	validate_file_ext(t_rt *rt)
{
	const char	*filename;
	const char	*dot;

	filename = rt->filename;
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (1);
	if (ft_strncmp(dot, ".rt\0", 4))
		return (1);
	return (0);
}

void	initialize_structs(char **argv, t_rt *rt)
{
	rt->filename = argv[1];
	if (validate_file_ext(rt))
	{
		ft_putendl_fd("Invalid file extension", 2);
		free(rt);
		exit(1);
	}
}
