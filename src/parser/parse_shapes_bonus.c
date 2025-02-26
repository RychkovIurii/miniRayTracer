/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:36:13 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/25 23:48:44 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	add_cone(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_CONE;
	rt->scene->shapes[i].closed = 1;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].center.y += rt->scene->shapes[i].height / 2;  //forced center.y to be higher by cone height
	rt->scene->shapes[i].normal = string_to_vector(normal);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shapes[i].material.ambient = rt->scene->ambient.ratio;
	rt->scene->shapes[i].material.diffuse = 0.8;
	rt->scene->shapes[i].material.specular = 0.4;
	rt->scene->shapes[i].material.shininess = 150.0;
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shapes[i].material.refractive_index = 1.0;
	rt->scene->shapes[i].material.reflective = 0.0;
	rt->scene->shapes[i].material.transparency = 0.0;
	rt->scene->shape_count++;
}

int	validate_cone_dimensions(char **element, t_rt *rt)
{
	double	diameter;
	double	cone_height;

	diameter = validate_dimension(element[3]);
	if (diameter == -1)
		return (error("Invalid cone diameter", 1));
	rt->scene->shapes[rt->scene->shape_count].radius = diameter / 2.0;
	cone_height = validate_dimension(element[4]);
	if (cone_height == -1)
		return (error("Invalid cone height", 1));
	rt->scene->shapes[rt->scene->shape_count].height = cone_height;
	rt->scene->shapes[rt->scene->shape_count].max = 0;
	rt->scene->shapes[rt->scene->shape_count].min = -cone_height;
	return (0);
}

int	parse_cone(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	char	**colors;

	if (validate_argument_count(element, 6))
		return (error("Invalid number of arguments for cone", 1));
	if (validate_cone_dimensions(element, rt))
	{
		print_error("Failed to validate cone dimensions");
		return (1);
	}
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for center of cone", 1));
	normal = validate_vector(element[2]);
	if (!normal)
	{
		free_array(coordinates);
		return (error("Invalid normal vector for cone", 1));
	}
	colors = validate_color(element[5]);
	if (!colors)
	{
		free_array(normal);
		free_array(coordinates);
		return (error("Invalid cone color", 1));
	}
	add_cone(rt, coordinates, normal, colors);
	return (0);
}