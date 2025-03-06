/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:41:55 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/06 21:13:34 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_double(char *str, double min, double max)
{
	double	value;
	int		error;

	value = ft_atof_error(str, &error);
	if (error || value < min || value > max)
		return (1);
	return (0);
}

double	validate_dimension(char *str)
{
	double	dimension;
	int		error;

	dimension = ft_atof_error(str, &error);
	if (error || dimension < EPSILON || dimension > 1000)
		return (-1);
	return (dimension);
}

int	invalid_file_content(t_rt *rt)
{
	if (rt->scene->camera.id == 0)
		return (error("Camera missing from file", 1));
	if (rt->scene->ambient.id == 0 && rt->scene->light.id == 0)
		return (error("Light source missing from file", 1));
	if (rt->scene->ambient.id != 0 && rt->scene->light.id == 0
		&& rt->scene->ambient.ratio == 0)
		return (error("At least one non-zero light source is required", 1));
	if (rt->scene->light.id != 0 && rt->scene->ambient.id == 0
		&& rt->scene->light.brightness == 0)
		return (error("At least one non-zero light source is required", 1));
	if (rt->scene->ambient.id != 0 && rt->scene->light.id != 0
		&& rt->scene->ambient.ratio == 0 && rt->scene->light.brightness == 0)
		return (error("At least one non-zero light source is required", 1));
	return (0);
}

t_file	validate_args(char **element, int coord_i, int normal_i, int color_i)
{
	t_file	data;

	ft_bzero(&data, sizeof(t_file));
	data.coordinates = validate_coordinates(element[coord_i]);
	if (!data.coordinates)
	{
		print_error("Invalid coordinates");
		return (data);
	}
	data.normal = validate_vector(element[normal_i]);
	if (!data.normal)
	{
		free_array(data.coordinates);
		print_error("Invalid normal vector");
		return (data);
	}
	data.colors = validate_color(element[color_i]);
	if (!data.colors)
	{
		free_array(data.normal);
		free_array(data.coordinates);
		print_error("Invalid color [0-255]");
	}
	return (data);
}
