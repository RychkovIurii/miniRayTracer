/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:27:49 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 14:54:49 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	validate_cone_dimensions(char **element, t_rt *rt)
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

int	parse_cone_bonus(char **element, t_rt *rt)
{
	t_file	data;
	t_shape	*cone;
	size_t	arg_count;

	arg_count = 16;
	if (validate_argument_count(element, arg_count))
		return (error("Invalid number of arguments for cone", 1));
	if (validate_cone_dimensions(element, rt))
		return (1);
	data = validate_args(element, 1, 2, 5);
	if (!data.coordinates || !data.normal || !data.colors)
		return (1);
	cone = add_cone_bonus(rt, data);
	return (add_material(element, &(cone->material), arg_count));
}
