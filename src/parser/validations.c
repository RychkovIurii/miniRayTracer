/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:35 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 19:46:47 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	**validate_color(char *str)
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
		color_value = rt_atoi(color_strings[i]);
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
		if (coordinate < -DBL_MAX || coordinate > DBL_MAX) // which boundaries to set??
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

t_element_data	validate_element_data(char **element)
{
	t_element_data	data;

	ft_bzero(&data, sizeof(t_element_data));
	data.coordinates = validate_coordinates(element[1]);
	if (!data.coordinates)
		print_error("Invalid coordinates for center");
	else if (!(data.normal = validate_vector(element[2])))
	{
		free_array(data.coordinates);
		print_error("Invalid normal vector");
	}
	else if (!(data.colors = validate_color(element[5])))
	{
		free_array(data.normal);
		free_array(data.coordinates);
		print_error("Invalid color");
	}
	return (data);
}

double	validate_ratio(char *str)
{
	double	ratio;

	ratio = ft_atof(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);
	return (ratio);
}

double	validate_dimension(char *str)
{
	double	dimension;

	dimension = ft_atof(str);
	if (dimension < EPSILON) // should there be a max limit??
		return (-1);
	return (dimension);
}
