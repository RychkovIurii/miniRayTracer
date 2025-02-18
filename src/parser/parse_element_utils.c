/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:09:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/18 19:29:23 by henbuska         ###   ########.fr       */
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

double	validate_ratio(char *str)
{
	double	ratio;
	
	ratio = ft_atof(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);
	return (ratio);
}

char **validate_color(char *str)
{
	int		color_value;
	char	**color_strings;
	int		i;
	
	color_strings = ft_split(str, ',');
	if (!color_strings)
		return (NULL);
	if (validate_argument_count(color_strings, 3))
	{
		free_array(color_strings);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		color_value = custom_atoi(color_strings[i]);
		if (color_value < 0 || color_value > 255)
		{
			free_array(color_strings);
			return (NULL);
		}
		i++;
	}
	return (color_strings);
}

char	**validate_coordinates(char *str)
{
	double	coordinate;
	char	**coord_strings;
	int		i;

	coord_strings = ft_split(str, ',');
	if (!coord_strings)
		return (NULL);
	if (validate_argument_count(coord_strings, 3))
	{
		free_array(coord_strings);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		coordinate = ft_atof(coord_strings[i]);
		if (coordinate < -DBL_MAX || coordinate > DBL_MAX)  // which boundaries to set??
		{
			free_array(coord_strings);
			return (NULL);
		}
		i++;
	}
	return (coord_strings);
}

char	**validate_vector(char *str)
{
	double	vector_element;
	char	**vector_strings;
	int		i;

	vector_strings = ft_split(str, ',');
	if (!vector_strings)
		return (NULL);
	if (validate_argument_count(vector_strings, 3))
	{
		free_array(vector_strings);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		vector_element = ft_atof(vector_strings[i]);
		if (vector_element < -1.0 || vector_element > 1.0)
		{
			free_array(vector_strings);
			return (NULL);
		}
		i++;
	}
	return (vector_strings);
}

int	validate_dimension(char *str)
{
	double	dimension;
	
	dimension = ft_atof(str);
	if (dimension < EPSILON)  // should there be a max limit??
		return (-1);
	return (dimension);
}
