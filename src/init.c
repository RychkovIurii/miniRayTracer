/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:17:37 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 17:33:07 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* t_material	material(t_tuple color, double ambient, double diffuse,
	double specular, double shininess, int has_pattern)
{
	t_material	material;

	material.color = color;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	material.has_pattern = has_pattern;
	material.reflective = 0.0;
	material.transparency = 0.0;
	material.refractive_index = 1.0;
	return (material);
} */

/* t_material default_material()
{
	t_material mat;
	mat.color = create_color(1, 1, 1);
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200.0;
	mat.has_pattern = 0;
	mat.reflective = 0.0;
	return (mat);
} */

t_light	init_light(t_tuple position, t_tuple color, double brightness)
{
	t_light	light;

	light.position = position;
	light.color = color;
	light.brightness = brightness;
	light.intensity = multiply_tuple_scalar(color, brightness);
	return (light);
}

void	init_scene_pixels(t_scene *scene, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	scene->height = height;
	scene->width = width;
	scene->pixels = malloc(height * sizeof(t_tuple *));
	if (!scene->pixels)
		exit(EXIT_FAILURE); // TODO: handle error
	while (i < height)
	{
		j = 0;
		scene->pixels[i] = malloc(width * sizeof(t_tuple));
		if (!scene->pixels[i])
			exit(EXIT_FAILURE); // TODO: handle error
		while (j < width)
		{
			scene->pixels[i][j] = create_color(0, 0, 0);
			j++;
		}
		i++;
	}
}

void	initialize_structs(char **argv, t_rt *rt)
{
	rt->filename = argv[1];
	if (validate_file_ext(rt))
	{
		printf("Invalid file extension\n");
		free(rt);
		exit(EXIT_FAILURE);
	}
}
