/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:08:22 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/18 20:05:45 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 1;
	rt->scene->shapes[i].center.x = ft_atof(coordinates[0]);
	rt->scene->shapes[i].center.y = ft_atof(coordinates[1]);
	rt->scene->shapes[i].center.z = ft_atof(coordinates[2]);
	rt->scene->shapes[i].radius = diameter / 2;
	rt->scene->shapes[i].material.color.x = ft_atof(colors[0])/255.0;
	rt->scene->shapes[i].material.color.y = ft_atof(colors[1])/255.0;
	rt->scene->shapes[i].material.color.z = ft_atof(colors[2])/255.0;
	rt->scene->shape_count++;
	free_array(coordinates);
	free_array(colors);

	printf("Shape type: %d\n", rt->scene->shapes[i].type);
	printf("Sphere center: %f, %f, %f\n", rt->scene->shapes[i].center.x, rt->scene->shapes[i].center.y, rt->scene->shapes[i].center.z);
	printf("Sphere radius: %f\n", rt->scene->shapes[i].radius);
	printf("Sphere color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
}

void	add_plane(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 2;
	rt->scene->shapes[i].point_on_plane.x = ft_atof(coordinates[0]);
	rt->scene->shapes[i].point_on_plane.y = ft_atof(coordinates[1]);
	rt->scene->shapes[i].point_on_plane.z = ft_atof(coordinates[2]);
	rt->scene->shapes[i].normal.x = ft_atof(normal[0]);
	rt->scene->shapes[i].normal.y = ft_atof(normal[1]);
	rt->scene->shapes[i].normal.z = ft_atof(normal[2]);
	rt->scene->shapes[i].material.color.x = ft_atof(colors[0])/255.0;
	rt->scene->shapes[i].material.color.y = ft_atof(colors[1])/255.0;
	rt->scene->shapes[i].material.color.z = ft_atof(colors[2])/255.0;;
	rt->scene->shape_count++;
	free_array(coordinates);
	free_array(normal);
	free_array(colors);

	printf("Plane type: %d\n", rt->scene->shapes[i].type);
	printf("Plane center: %f, %f, %f\n", rt->scene->shapes[i].point_on_plane.x, rt->scene->shapes[i].point_on_plane.y, rt->scene->shapes[i].point_on_plane.z);
	printf("Plane normal:%f, %f, %f\n", rt->scene->shapes[i].normal.x, rt->scene->shapes[i].normal.y, rt->scene->shapes[i].normal.z);
	printf("Plane color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
}

void	add_cylinder(t_rt *rt, char **coordinates, char** normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 3;
	rt->scene->shapes[i].center.x = ft_atof(coordinates[0]);
	rt->scene->shapes[i].center.y = ft_atof(coordinates[1]);
	rt->scene->shapes[i].center.z = ft_atof(coordinates[2]);
	rt->scene->shapes[i].normal.x = ft_atof(normal[0]);
	rt->scene->shapes[i].normal.y = ft_atof(normal[1]);
	rt->scene->shapes[i].normal.z = ft_atof(normal[2]);
	rt->scene->shapes[i].material.color.x = ft_atof(colors[0])/255.0;
	rt->scene->shapes[i].material.color.y = ft_atof(colors[1])/255.0;
	rt->scene->shapes[i].material.color.z = ft_atof(colors[2])/255.0;
	rt->scene->shape_count++;
	free_array(coordinates);
	free_array(normal);
	free_array(colors);

	printf("Cylinder type: %d\n", rt->scene->shapes[i].type);
	printf("Cylinder center: %f, %f, %f\n", rt->scene->shapes[i].center.x, rt->scene->shapes[i].center.y, rt->scene->shapes[i].center.z);
	printf("Cylinder normal:%f, %f, %f\n", rt->scene->shapes[i].normal.x, rt->scene->shapes[i].normal.y, rt->scene->shapes[i].normal.z);
	printf("Cylinder color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
}


int	parse_sphere(char **element, t_rt *rt)
{
	char	**coordinates;
	double	diameter;
	char	**colors;
	
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for sphere", 1));
	diameter = validate_dimension(element[2]);
	if (diameter == -1)
		return (error("Invalid sphere diameter", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for sphere center", 1));
	colors = validate_color(element[3]);
	if (!colors)
	{
		free_array(coordinates);
		return (error("Invalid sphere color", 1));
	}
	add_sphere(rt, coordinates, colors, diameter);
	return (0);
}

int	parse_plane(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	char	**colors;
	
	
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for plane", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for point in plane", 1));
	normal = validate_vector(element[2]);
	if (!normal)
	{
		free_array(coordinates);
		return (error("Invalid normal vector for plane", 1));
	}
	colors = validate_color(element[3]);
	if (!colors)
	{
		free_array(coordinates);
		free_array(colors);
		return (error("Invalid plane color", 1));
	}
	add_plane(rt, coordinates, normal, colors);
	return (0);
}

int	parse_cylinder(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**normal;
	double	diameter;
	double	cylinder_height;
	char	**colors;
	
	if (validate_argument_count(element, 6))
		return (error("Invalid number of arguments for cylinder", 1));
	diameter = validate_dimension(element[3]);
	if (diameter == -1)
		return (error("Invalid cylinder diameter", 1));
	rt->scene->shapes[rt->scene->shape_count].radius = diameter / 2.0;
	printf("Cylinder radius: %f\n", rt->scene->shapes[rt->scene->shape_count].radius);
	cylinder_height = validate_dimension(element[4]);
	if (cylinder_height == -1)
		return (error("Invalid cylinder height", 1));
	rt->scene->shapes[rt->scene->shape_count].cylinder_height = cylinder_height;
	printf("Cylinder height: %f\n", rt->scene->shapes[rt->scene->shape_count].cylinder_height);
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for center of cylinder", 1));
	normal = validate_vector(element[2]);
	if (!normal)
	{
		free_array(coordinates);
		return (error("Invalid normal vector for cylinder", 1));
	}
	colors = validate_color(element[5]);
	if (!colors)
	{
		free_array(coordinates);
		return (error("Invalid cylinder color", 1));
	}
	add_cylinder(rt, coordinates, normal, colors);
	return (0);
}
