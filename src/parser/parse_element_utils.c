/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:09:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/17 19:51:50 by henbuska         ###   ########.fr       */
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
	{
		print_error("Invalid number of arguments in element");
		return (1);
	}
	return (0);
}

int	validate_colors(char **colors)
{
	int		color_value;
	int		i;
	
	if (validate_argument_count(colors, 3))
		return (1);
	i = 0;
	while (i < 3)
	{
		color_value = custom_atoi(colors[i]);
		if (color_value < 0 || color_value > 255)
		{
			free_array(colors);
			print_error("Invalid color value");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_coordinates(char **coordinates)
{
	double	coord;
	int		i;

	if (validate_argument_count(coordinates, 3))
		return (1);
	i = 0;
	while (i < 3)
	{
		coord = ft_atof(coordinates[i]);
		if (coord < DBL_MIN || coord > DBL_MAX)
		{
			free_array(coordinates);
			print_error("Invalid coordinate value");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_vector(char **orient_vector)
{
	double	value;
	int		i;

	if (validate_argument_count(orient_vector, 3))
		return (1);
	i = 0;
	while (i < 3)
	{
		value = ft_atof(orient_vector[i]);
		if (value < -1.0 || value > 1.0)
		{
			free_array(orient_vector);
			print_error("Invalid orientation vector value");
			return (1);
		}
		i++;
	}
	return (0);
}
