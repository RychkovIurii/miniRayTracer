/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_non_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:42:23 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/24 18:42:55 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient(char **element, t_rt *rt)
{
	double	ambient;
	char	**colors;

	if (rt->scene->ambient.id != 0)
		return (error("Too many ambient lights in file", 1));
	if (validate_argument_count(element, 3))
		return (error("Invalid number of arguments for ambient", 1));
	ambient = validate_ratio(element[1]);
	if (ambient == -1)
		return (error("Invalid ambient lighting ratio [0.0-1.0]", 1));
	colors = validate_color(element[2]);
	if (!colors)
		return (error("Invalid color for ambient", 1));
	rt->scene->ambient.ratio = ambient;
	rt->scene->ambient.color = string_to_color(colors);
	rt->scene->ambient.id = 1;
	return (0);
}

int	parse_camera(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	int		fov;

	if (rt->scene->camera.id != 0)
		return (error("Too many cameras in file", 1));
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for camera", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for camera view point", 1));
	rt->scene->camera.view_point = string_to_point(coordinates);
	normal = validate_vector(element[2]);
	if (!normal)
		return (error("Invalid orientation vector for camera", 1));
	rt->scene->camera.normal = string_to_vector(normal);
	fov = rt_atoi(element[3]);
	if (fov < 0 || fov > 180)
		return (error("Invalid field of view for camera", 1));
	rt->scene->camera.field_of_view = fov;
	rt->scene->camera.id = 1;
	return (0);
}

int	parse_light(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**colors;
	double	brightness;

	if (rt->scene->light.id != 0)
		return (error("Too many lights in file", 1));
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for light", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for light point", 1));
	rt->scene->light.position = string_to_point(coordinates);
	brightness = validate_ratio(element[2]);
	if (brightness == -1)
		return (error("Invalid brightness for light [0.0-1.0]", 1));
	rt->scene->light.brightness = brightness;
	colors = validate_color(element[3]);
	if (!colors)
		return (error("Invalid color for light", 1));
	rt->scene->light.color = string_to_color(colors);
	rt->scene->light.id = 1;
	return (0);
}
