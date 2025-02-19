/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:58:50 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/19 14:46:53 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient(char **element, t_rt *rt)
{
	double	ambient;
	char	**colors;
	
	if (rt->scene->ambient.id != 0)
		return (error("Too many ambient lights in file", 1));
	if (validate_argument_count(element, 3))
		return (error("Invalid number of arguments for ambient", 1));
	ambient = validate_ratio(element[1]);
	if (ambient == -1)
		return (error("Invalid ambient lighting ratio [0.0-1.0]", 1));
	colors = validate_color(element[2]);
	if (!colors)
		return (error("Invalid color for ambient", 1));
	rt->scene->ambient.ratio = ambient;
	rt->scene->ambient.color.x = 255.0/custom_atoi(colors[0]);
	rt->scene->ambient.color.y = 255.0/custom_atoi(colors[1]);
	rt->scene->ambient.color.z = 255.0/custom_atoi(colors[2]);
	rt->scene->ambient.id = 1;
	free_array(colors);
	printf("Ambient ratio: %f, colors: %f, %f, %f\n", rt->scene->ambient.ratio, rt->scene->ambient.color.x, rt->scene->ambient.color.y, rt->scene->ambient.color.z);
	return (0);
}

int	parse_camera(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	int		fov;

	if (rt->scene->camera.id != 0)
		return (error("Too many cameras in file", 1));
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for camera", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for camera view point", 1));
	rt->scene->camera.view_point.x = ft_atof(coordinates[0]);
	rt->scene->camera.view_point.y = ft_atof(coordinates[1]);
	rt->scene->camera.view_point.z = ft_atof(coordinates[2]);
	free_array(coordinates);
	printf("Camera view point: %f, %f, %f\n", rt->scene->camera.view_point.x, rt->scene->camera.view_point.y, rt->scene->camera.view_point.z);
	normal = validate_vector(element[2]);
	if (!normal)
		return (error("Invalid orientation vector for camera", 1));
	rt->scene->camera.normal.x = ft_atof(normal[0]);
	rt->scene->camera.normal.y = ft_atof(normal[1]);
	rt->scene->camera.normal.z = ft_atof(normal[2]);
	free_array(normal);
	printf("Camera normal vector: %f, %f, %f\n", rt->scene->camera.normal.x, rt->scene->camera.normal.y, rt->scene->camera.normal.z);
	fov = custom_atoi(element[3]);
	if (fov < 0 || fov > 180)
		return (error("Invalid field of view for camera", 1));
	rt->scene->camera.field_of_view = fov;
	rt->scene->camera.id = 1;
	printf("Camera fow: %f\n", rt->scene->camera.field_of_view);
	return (0);
}

int	parse_light(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**colors;
	double	brightness;
	
	if (rt->scene->light.id != 0)
		return (error("Too many lights in file", 1));
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for light", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for light point", 1));
	rt->scene->light.position.x = ft_atof(coordinates[0]);
	rt->scene->light.position.y = ft_atof(coordinates[1]);
	rt->scene->light.position.z = ft_atof(coordinates[2]);
	free_array(coordinates);
	printf("Light point: %f, %f, %f\n", rt->scene->light.position.x, rt->scene->light.position.y, rt->scene->light.position.z);
	brightness = validate_ratio(element[2]);
	if (brightness == -1)
		return (error("Invalid brightness for light [0.0-1.0]", 1));
	rt->scene->light.brightness = brightness;
	printf("Light brightness: %f\n", rt->scene->light.brightness);
	colors = validate_color(element[3]);
	if (!colors)
		return (error("Invalid color for light", 1));
	rt->scene->light.color.x = 255.0/custom_atoi(colors[0]);
	rt->scene->light.color.y = 255.0/custom_atoi(colors[1]);
	rt->scene->light.color.z = 255.0/custom_atoi(colors[2]);
	rt->scene->light.id = 1;
	free_array(colors);
	printf("Light color: %f, %f, %f\n", rt->scene->light.color.x, rt->scene->light.color.y, rt->scene->light.color.z);
	return (0);
}

int	parse_element(char **element, t_rt *rt)
{
	if (ft_strcmp(element[0], "A") == 0)
		return(parse_ambient(element, rt));
	else if (ft_strcmp(element[0], "C") == 0)
		return (parse_camera(element, rt));
	else if (ft_strcmp(element[0], "L") == 0)
		return (parse_light(element, rt));
	else if (ft_strcmp(element[0], "sp") == 0)
		return (parse_sphere(element, rt));
	else if (ft_strcmp(element[0], "pl") == 0)
		return (parse_plane(element, rt));
	else if (ft_strcmp(element[0], "cy") == 0)
		return(parse_cylinder(element, rt));
	else
	{
		printf("Invalid element identifier\n");
		return (1);
	}
	return (0);
}
