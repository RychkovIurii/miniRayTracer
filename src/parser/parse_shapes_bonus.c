/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:36:13 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 16:40:38 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(char **element, t_rt *rt)
{
	char		**coordinates;
	double		diameter;
	char		**colors;
	size_t		arg_count;
	t_shape		*sphere;

	arg_count = 10;
	if (validate_argument_count(element, arg_count))
		return (error("Invalid number of arguments for sphere", 1));
	diameter = validate_dimension(element[2]);
	if (diameter == -1)
		return (error("Invalid sphere diameter", 1));
	rt->scene->shapes[rt->scene->shape_count].radius = diameter / 2.0;
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for sphere center", 1));
	colors = validate_color(element[3]);
	if (!colors)
	{
		free_array(coordinates);
		return (error("Invalid sphere color", 1));
	}
	sphere = add_sphere(rt, coordinates, colors, diameter);
	return (add_material(element, &(sphere->material), arg_count));
}

int	parse_plane(char **element, t_rt *rt)
{
	char		**coordinates;
	char		**normal;
	char		**colors;
	size_t		arg_count;
	t_shape		*plane;

	arg_count = 10;
	if (validate_argument_count(element, arg_count))
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
		free_arrays(normal, coordinates);
		return (error("Invalid plane color", 1));
	}
	plane = add_plane(rt, coordinates, normal, colors);
	return (add_material(element, &(plane->material), arg_count));
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
	rt->scene->shapes[rt->scene->shape_count].height = cylinder_height;
	rt->scene->shapes[rt->scene->shape_count].min = -cylinder_height / 2.0;
	rt->scene->shapes[rt->scene->shape_count].max = cylinder_height / 2.0;
	return (0);
}

int	parse_cylinder(char **element, t_rt *rt)
{
	char		**coordinates;
	char		**normal;
	char		**colors;
	size_t		arg_count;
	t_shape		*cylinder;

	arg_count = 12;
	if (validate_argument_count(element, arg_count))
		return (error("Invalid number of arguments for cylinder", 1));
	if (validate_cylinder_dimensions(element, rt))
		return (1);
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
		free_arrays(normal, coordinates);
		return (error("Invalid cylinder color", 1));
	}
	cylinder = add_cylinder(rt, coordinates, normal, colors);
	return (add_material(element, &(cylinder->material), arg_count));
}


