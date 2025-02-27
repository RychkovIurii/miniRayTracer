/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:20:58 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 19:20:45 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern)
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
}

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

t_ray	ray_for_pixel(t_camera camera, int px, int py, t_tuple origin)
{
	double xoffset = (px + 0.5) * camera.pixel_size;
	double yoffset = (py + 0.5) * camera.pixel_size;

	double world_x = camera.half_width - xoffset;
	double world_y = camera.half_height - yoffset;


	t_tuple pixel = multiply_matrix_by_tuple(camera.transform_inv, point(world_x, world_y, -1));
	t_tuple direction = normalize(substract_tuple(pixel, origin));

	return (create_ray(origin, direction));
}

void	render(t_camera camera, t_scene *scene)
{
	t_tuple origin;

	camera.transform_inv = inverse_matrix(camera.transform);
	origin = multiply_matrix_by_tuple(camera.transform_inv, point(0, 0, 0));
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray ray = ray_for_pixel(camera, x, y, origin);
			scene->pixels[y][x] = color_at(scene, ray, DEFAULT_REMAINING);
		}
	}
}



t_light	init_light(t_tuple position, t_tuple color, double brightness)
{
	t_light	light;

	light.position = position;
	light.color = color;
	light.brightness = brightness;
	light.intensity = multiply_tuple_scalar(color, brightness);

	return (light);
}
