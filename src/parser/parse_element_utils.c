/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:09:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/28 16:06:45 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_argument_count(char **array, int count)
{
	int	arg_count;
	int	i;

	arg_count = 0;
	i = 0;
	while (array[i])
	{
		arg_count++;
		i++;
	}
	if (arg_count != count)
		return (1);
	return (0);
}

t_tuple	string_to_point(char **strings)
{
	t_tuple	point;

	point.x = ft_atof(strings[0]);
	point.y = ft_atof(strings[1]);
	point.z = ft_atof(strings[2]);
	point.w = 1.0;
	free_array(strings);
	return (point);
}

t_tuple	string_to_vector(char **strings)
{
	t_tuple	vector;

	vector.x = ft_atof(strings[0]);
	vector.y = ft_atof(strings[1]);
	vector.z = ft_atof(strings[2]);
	vector.w = 0.0;
	free_array(strings);
	return (vector);
}

t_tuple	string_to_color(char **strings)
{
	t_tuple	color;

	color.x = ft_atof(strings[0]) / 255.0;
	color.y = ft_atof(strings[1]) / 255.0;
	color.z = ft_atof(strings[2]) / 255.0;
	free_array(strings);
	return (color);
}

double	validate_dimension(char *str)
{
	double	dimension;

	dimension = ft_atof(str);
	if (dimension < EPSILON) // should there be a max limit??
		return (-1);
	return (dimension);
}
