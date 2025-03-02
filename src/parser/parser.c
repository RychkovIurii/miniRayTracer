/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/02 16:48:17 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <fcntl.h>

void	print_parsed_content(t_rt *rt)
{
	printf("***Ambient***\n");
	printf("Ambient ratio: %f\n", rt->scene->ambient.ratio);
	printf("Ambient color: %f, %f, %f\n", rt->scene->ambient.color.x, rt->scene->ambient.color.y, rt->scene->ambient.color.z);
	printf("***Camera***\n");
	printf("Camera view point: %f, %f, %f\n", rt->scene->camera.view_point.x, rt->scene->camera.view_point.y, rt->scene->camera.view_point.z);
	printf("Camera normal vector: %f, %f, %f\n", rt->scene->camera.normal.x, rt->scene->camera.normal.y, rt->scene->camera.normal.z);
	printf("Camera fow: %f\n", rt->scene->camera.field_of_view);
	printf("***Light***\n");
	printf("Light point: %f, %f, %f\n", rt->scene->light.position.x, rt->scene->light.position.y, rt->scene->light.position.z);
	printf("Light brightness: %f\n", rt->scene->light.brightness);
	printf("Light color: %f, %f, %f\n", rt->scene->light.color.x, rt->scene->light.color.y, rt->scene->light.color.z);
	printf("***Shapes***\n");
	printf("Shape count: %d\n", rt->scene->shape_count);
	int i = 0;
	while (i < rt->scene->shape_count)
	{
		t_shape	shape = rt->scene->shapes[i];
		if (shape.type == SHAPE_SPHERE)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Sphere center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Sphere radius: %f\n", shape.radius);
			printf("Sphere color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Sphere diffuse: %f\n", shape.material.diffuse);
			printf("Sphere specular: %f\n", shape.material.specular);
			printf("Sphere shininess: %f\n", shape.material.shininess);
			printf("Sphere reflective: %f\n", shape.material.reflective);
			printf("Sphere transparency: %f\n", shape.material.transparency);
			printf("Sphere refractive index: %f\n", shape.material.refractive_index);
		}
		else if (shape.type == SHAPE_PLANE)
		{
			printf("Shape type: %d\n", rt->scene->shapes[i].type);
			printf("Plane center: %f, %f, %f\n", shape.point_on_plane.x, shape.point_on_plane.y, shape.point_on_plane.z);
			printf("Plane normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Plane color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Plane diffuse: %f\n", shape.material.diffuse);
			printf("Plane specular: %f\n", shape.material.specular);
			printf("Plane shininess: %f\n", shape.material.shininess);
			printf("Plane reflective: %f\n", shape.material.reflective);
			printf("Plane refractive index: %f\n", shape.material.refractive_index);
			printf("Plane transparency: %f\n", shape.material.transparency);
		}
		else if (shape.type == SHAPE_CYLINDER)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Cylinder center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Cylinder normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Cylinder radius: %f\n", shape.radius);
			printf("Cylinder height: %f\n", shape.height);
			printf("Cylinder color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Cylinder diffuse: %f\n", shape.material.diffuse);
			printf("Cylinder specular: %f\n", shape.material.specular);
			printf("Cylinder shininess: %f\n", shape.material.shininess);
			printf("Cylinder reflective: %f\n", shape.material.reflective);
			printf("Cylinder transparency: %f\n", shape.material.transparency);
			printf("Cylinder refractive index: %f\n", shape.material.refractive_index);
		}
		else if (shape.type == SHAPE_CONE)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Cone center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Cone normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Cone radius: %f\n", shape.radius);
			printf("Cone height: %f\n", shape.height);
			printf("Cone color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Cone diffuse: %f\n", shape.material.diffuse);
			printf("Cone specular: %f\n", shape.material.specular);
			printf("Cone shininess: %f\n", shape.material.shininess);
			printf("Cone reflective: %f\n", shape.material.reflective);
			printf("Cone transparency: %f\n", shape.material.transparency);
			printf("Cone refractive index: %f\n", shape.material.refractive_index);
		}
		i++;
	}
}

char	**read_file_lines(int fd, int count)
{
	char	**lines;
	char	*line;
	int		i;

	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
	{
		print_error("Failed to allocate memory for lines");
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0' && line[0] != '\n')
			lines[i++] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	return (lines);
}

char	**read_file(t_rt *rt, int fd)
{
	rt->element_count = count_lines_in_file(fd);
	close(fd);
	if (rt->element_count <= 0)
		return (NULL);
	fd = open(rt->filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Could not open file");
		return (NULL);
	}
	return (read_file_lines(fd, rt->element_count));
}

int	parse_line(char *line, t_rt *rt)
{
	char	*trimmed;
	char	**element;
	int		status;

	trimmed = trim_extra_spaces(line);
	if (!trimmed)
	{
		print_error("Failed to trim line");
		return (1);
	}
	element = ft_split(trimmed, ' ');
	free(trimmed);
	if (!element)
		return (print_error("Failed to split line"), 1);
	status = parse_element(element, rt);
	if (status)
		printf("Failed to parse line %s", line);
	free_array(element);
	return (status);
}

int	parse_file_lines(char **lines, t_rt *rt)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], rt))
			return (1);
		i++;
	}
	return (0);
}

int	parse_file(t_rt *rt)
{
	int		fd;
	char	**lines;

	fd = open(rt->filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Could not open file");
		return (1);
	}
	lines = read_file(rt, fd);
	if (!lines)
		return (error("Failed to read file", 1));
	if (init_scene_structs(lines, rt) || parse_file_lines(lines, rt))
		return (free_and_return(NULL, lines, 1));
	free_array(lines);
	if (invalid_file_content(rt))
		return (printf("Invalid file content\n"), 1);
	print_parsed_content(rt);
	return (0);
}
