/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:08:22 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/06 21:14:22 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	t_file	data;

	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for plane", 1));
	data = validate_args(element, 1, 2, 3);
	if (!data.coordinates || !data.normal || !data.colors)
		return (1);
	add_plane(rt, data);
	return (0);
}

static int	validate_cylinder_dimensions(char **element, t_rt *rt)
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
	rt->scene->shapes[rt->scene->shape_count].height = cylinder_height;
	rt->scene->shapes[rt->scene->shape_count].min = -cylinder_height / 2.0;
	rt->scene->shapes[rt->scene->shape_count].max = cylinder_height / 2.0;
	return (0);
}

int	parse_cylinder(char **element, t_rt *rt)
{
	t_file	data;

	if (validate_argument_count(element, 6))
		return (error("Invalid number of arguments for cylinder", 1));
	if (validate_cylinder_dimensions(element, rt))
		return (1);
	data = validate_args(element, 1, 2, 5);
	if (!data.coordinates || !data.normal || !data.colors)
		return (1);
	add_cylinder(rt, data);
	return (0);
}
