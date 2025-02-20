/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/20 13:17:29 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
	int i = 0;
	while (i < rt->scene->shape_count)
	{
		if (rt->scene->shapes[i].type == 1)
		{
			printf("Shape type: %d\n", rt->scene->shapes[i].type);
			printf("Sphere center: %f, %f, %f\n", rt->scene->shapes[i].center.x, rt->scene->shapes[i].center.y, rt->scene->shapes[i].center.z);
			printf("Sphere radius: %f\n", rt->scene->shapes[i].radius);
			printf("Sphere color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
		}
		else if (rt->scene->shapes[i].type == 2)
		{
			printf("Shape type: %d\n", rt->scene->shapes[i].type);
			printf("Plane center: %f, %f, %f\n", rt->scene->shapes[i].point_on_plane.x, rt->scene->shapes[i].point_on_plane.y, rt->scene->shapes[i].point_on_plane.z);
			printf("Plane normal:%f, %f, %f\n", rt->scene->shapes[i].normal.x, rt->scene->shapes[i].normal.y, rt->scene->shapes[i].normal.z);
			printf("Plane color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
		}
		else if (rt->scene->shapes[i].type == 3)
		{
			printf("Shape type: %d\n", rt->scene->shapes[i].type);
			printf("Cylinder center: %f, %f, %f\n", rt->scene->shapes[i].center.x, rt->scene->shapes[i].center.y, rt->scene->shapes[i].center.z);
			printf("Cylinder normal:%f, %f, %f\n", rt->scene->shapes[i].normal.x, rt->scene->shapes[i].normal.y, rt->scene->shapes[i].normal.z);
			printf("Cylinder radius: %f\n", rt->scene->shapes[i].radius);
			printf("Cylinder height: %f\n", rt->scene->shapes[i].cylinder_height);
			printf("Cylinder color: %f, %f, %f\n", rt->scene->shapes[i].material.color.x, rt->scene->shapes[i].material.color.y, rt->scene->shapes[i].material.color.z);
		}
		i++;
	}
}

char	**allocate_lines(int count)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
	{
		print_error("Failed to allocate memory for lines");
		return (NULL);
	}
	return (lines);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Could not open file");
	return (fd);
}

char	**read_file(t_rt *rt, int fd)
{
	char	**lines;
	char	*line;
	int		i;

	rt->element_count = count_lines_in_file(fd);
	close(fd);
	if (rt->element_count <= 0)
		return (NULL);
	lines = allocate_lines(rt->element_count);
	if (!lines)
		return (NULL);
	fd = open_file(rt->filename);
	if (fd < 0)
		return (NULL);
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
	close(fd);
	return (lines);
}

int	parse_line(char *line, t_rt *rt)
{
	char	*trimmed;
	char	**element;

	trimmed = trim_extra_spaces(line);
	if (!trimmed)
		return (1);
	element = ft_split(trimmed, ' ');
	free(trimmed);
	if (!element)
		return (1);
	if (parse_element(element, rt))
	{
		free_array(element);
		return (1);
	}
	free_array(element);
	return (0);
}

int	parse_file(t_rt *rt)
{
	int		fd;
	char	**lines;
	int		i;

	fd = open_file(rt->filename);
	if (fd < 0)
		return (1);
	lines = read_file(rt, fd);
	if (!lines)
		return (1);
	if (init_scene_structs(rt))
		return (free_and_return(rt, lines, 1));
	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], rt))
			return (free_and_return(rt, lines, 1));
		i++;
	}
	free_array(lines);
	if (invalid_file_content(rt))
	{
		free_rt(rt);
		return (1);
	}
	print_parsed_content(rt);
	return (0);
}
