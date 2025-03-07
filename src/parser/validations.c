/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:35 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/07 10:01:00 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	has_invalid_commas(char *str, char delimiter)
{
	size_t	len;
	int		commas;

	commas = 0;
	if (!str || *str == '\0')
		return (1);
	len = ft_strlen(str);
	if (str[0] == delimiter || str[len - 1] == delimiter)
		return (1);
	while (*str)
	{
		if (*str == delimiter)
			commas++;
		str++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

char	**validate_color(char *str)
{
	int		color_value;
	char	**color_strings;
	int		i;

	if (has_invalid_commas(str, ','))
		return (NULL);
	color_strings = ft_split(str, ',');
	if (!color_strings || validate_argument_count(color_strings, 3))
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
	int		error;

	if (has_invalid_commas(str, ','))
		return (NULL);
	coord_strings = ft_split(str, ',');
	if (!coord_strings || validate_argument_count(coord_strings, 3))
	{
		free_array(coord_strings);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		coordinate = ft_atof_error(coord_strings[i], &error);
		if (error || coordinate < -1000.0 || coordinate > 1000.0)
		{
			free_array(coord_strings);
			return (NULL);
		}
		i++;
	}
	return (coord_strings);
}

static int	validate_vector_components(char **vector_strings)
{
	double	vector_element;
	double	sum_of_squares;
	int		error;
	int		i;

	sum_of_squares = 0;
	i = 0;
	while (i < 3)
	{
		vector_element = ft_atof_error(vector_strings[i], &error);
		if (error || vector_element < -1.0 || vector_element > 1.0)
			return (0);
		sum_of_squares += vector_element * vector_element;
		i++;
	}
	return (fabs(sum_of_squares - 1.0) < 0.01);
}

char	**validate_vector(char *str)
{
	char	**vector_strings;

	if (has_invalid_commas(str, ','))
		return (NULL);
	vector_strings = ft_split(str, ',');
	if (!vector_strings)
		return (NULL);
	if (validate_argument_count(vector_strings, 3))
	{
		free_array(vector_strings);
		return (NULL);
	}
	if (!validate_vector_components(vector_strings))
	{
		free_array(vector_strings);
		return (NULL);
	}
	return (vector_strings);
}
