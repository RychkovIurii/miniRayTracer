/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:08:22 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/23 21:55:55 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(char **element, t_rt *rt)
{
	char	**coordinates;
	double	diameter;
	char	**colors;

	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for sphere", 1));
	diameter = validate_dimension(element[2]);
	if (diameter == -1)
		return (error("Invalid sphere diameter", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for sphere center", 1));
	colors = validate_color(element[3]);
	if (!colors)
	{
		free_array(coordinates);
		return (error("Invalid sphere color", 1));
	}
	add_sphere(rt, coordinates, colors, diameter);
	return (0);
}

int	parse_plane(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	char	**colors;

	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for plane", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for point in plane", 1));
	normal = validate_vector(element[2]);
	if (!normal)
	{
		free_array(coordinates);
		return (error("Invalid normal vector for plane", 1));
	}
	colors = validate_color(element[3]);
	if (!colors)
	{
		free_array(coordinates);
		free_array(colors);
		return (error("Invalid plane color", 1));
	}
	add_plane(rt, coordinates, normal, colors);
	return (0);
}

int	validate_cylinder_dimensions(char **element, t_rt *rt)
{
	double	diameter;
	double	cylinder_height;

	diameter = validate_dimension(element[3]);
	if (diameter == -1)
		return (error("Invalid cylinder diameter", 1));
	rt->scene->shapes[rt->scene->shape_count].radius = diameter / 2.0;
	cylinder_height = validate_dimension(element[4]);
	if (cylinder_height == -1)
		return (error("Invalid cylinder height", 1));
	rt->scene->shapes[rt->scene->shape_count].cylinder_height = cylinder_height;
	rt->scene->shapes[rt->scene->shape_count].min = -cylinder_height / 2.0;
	rt->scene->shapes[rt->scene->shape_count].max = cylinder_height / 2.0;
	return (0);
}

int	parse_cylinder(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	char	**colors;

	if (validate_argument_count(element, 6))
		return (error("Invalid number of arguments for cylinder", 1));
	if (validate_cylinder_dimensions(element, rt))
	{
		print_error("Failed to validate cylinder dimensions");
		return (1);
	}
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for center of cylinder", 1));
	normal = validate_vector(element[2]);
	if (!normal)
	{
		free_array(coordinates);
		return (error("Invalid normal vector for cylinder", 1));
	}
	colors = validate_color(element[5]);
	if (!colors)
	{
		free_array(normal);
		free_array(coordinates);
		return (error("Invalid cylinder color", 1));
	}
	add_cylinder(rt, coordinates, normal, colors);
	return (0);
}
