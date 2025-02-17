/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:58:50 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/17 20:23:58 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient(char **element, t_rt *rt)
{
	double	ambient;
	char	**colors;

	if (validate_argument_count(element, 3))
		return (1);
	ambient = ft_atof(element[1]);
	if (ambient < 0.0 || ambient > 1.0)
	{
		print_error("Invalid ambient lighting ratio");
		return (1);
	}
	colors = ft_split(element[2], ',');
	if (!colors)
		return (1);
	if (validate_colors(colors))
		return (1);
	if (allocate_and_init_scene(rt))
	{
		free_array(colors);
		return (1);
	}
	rt->scene->ambient.ratio = ambient;
	rt->scene->ambient.color.x = 255.0/custom_atoi(colors[0]);
	rt->scene->ambient.color.y = 255.0/custom_atoi(colors[1]);
	rt->scene->ambient.color.z = 255.0/custom_atoi(colors[2]);
	free_array(colors);
	//printf("Ambient ratio: %f, colors: %f, %f, %f\n", rt->scene->ambient.ratio, rt->scene->ambient.color.x, rt->scene->ambient.color.y, rt->scene->ambient.color.z);
	return (0);
}

int	parse_camera(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	int		fov;
	
	if (validate_argument_count(element, 4))
		return (1);
	coordinates = ft_split(element[1], ',');
	if (!coordinates)
		return (1);
	if (validate_coordinates(coordinates))
		return (1);
	
	rt->scene->camera->view_point.x = ft_atof(coordinates[0]);
	rt->scene->camera->view_point.y = ft_atof(coordinates[1]);
	rt->scene->camera->view_point.z = ft_atof(coordinates[2]);
	free_array(coordinates);
	printf("Camera view point: %f, %f, %f\n", rt->scene->camera->view_point.x, rt->scene->camera->view_point.y, rt->scene->camera->view_point.z);
	normal = ft_split(element[2], ',');
	if (!normal)
		return (1);
	if (validate_vector(normal))
		return (1);
	rt->scene->camera->normal.x = ft_atof(normal[0]);
	rt->scene->camera->normal.y = ft_atof(normal[1]);
	rt->scene->camera->normal.z = ft_atof(normal[2]);
	fov = custom_atoi(element[3]);
	if (fov < 0 || fov > 180)
	{
		print_error("Invalid field of view");
		return (1);
	}
	rt->scene->camera->field_of_view = fov;
	return (0);
}

int	parse_element(char **element, t_rt *rt)
{
	if (ft_strncmp(element[0], "A", 2) == 0 && element[0][1] == '\0')
		parse_ambient(element, rt);
	else if (ft_strncmp(element[0], "C", 2) == 0 && element[0][1] == '\0')
		parse_camera(element, rt);
	else
	{
		print_error("Invalid element identifier");
		return (1);
	}
	/*
	else if (ft_strncmp(element[0], "L", 1) && element[0][1] == '\0')
		parse_light(element, rt);
	else if (ft_strncmp(element[0], "sp", 2) && element[0][2] == '\0')
		parse_sphere(element, rt);
	else if (ft_strncmp(element[0], "pl", 2) && element[0][2] == '\0')
		parse_plane(element, rt);
	else if (ft_strncmp(element[0], "cy", 2) && element[0][2] == '\0')
		parse_cylinder(element, rt);
	else
	{
		printf("Invalid element identifier\n");
		return (1);
	} */
	return (0);
}

// validate number of arguments in element
// validate argument values
// validate rgb 
// validate ambient ratio