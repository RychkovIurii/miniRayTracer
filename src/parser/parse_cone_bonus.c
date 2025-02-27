/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:27:49 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 16:34:20 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	char		**coordinates;
	char		**normal;
	char		**colors;
	size_t		arg_count;
	t_shape		*cone;

	arg_count = 12;
	if (validate_argument_count(element, arg_count))
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
		free_arrays(normal, coordinates);
		return (error("Invalid cone color", 1));
	}
	cone = add_cone(rt, coordinates, normal, colors);
	return (add_material(element, &(cone->material), arg_count));
}
