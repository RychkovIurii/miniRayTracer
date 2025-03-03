/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:43:18 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 18:59:56 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	error(char *message, int ret)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (ret);
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

int	count_lines_in_file(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0' && ft_strlen(line) > 0 && line[0] != '\n')
			line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (line_count);
}

static int	count_non_shape_elements(char **lines)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'A' || lines[i][0] == 'L' || lines[i][0] == 'C')
			count++;
		i++;
	}
	return (count);
}

int	init_scene_structs(char **lines, t_rt *rt)
{
	int	non_shape;

	rt->scene = ft_calloc(1, sizeof(t_scene));
	if (!rt->scene)
	{
		print_error("Failed to allocate t_scene");
		return (1);
	}
	non_shape = count_non_shape_elements(lines);
	rt->scene->shape_count = 0;
	rt->scene->needs_render = 1;
	rt->scene->shapes = ft_calloc(rt->element_count - non_shape, sizeof(t_shape));
	if (!rt->scene->shapes)
	{
		print_error("Failed to allocate shapes array");
		return (1);
	}
	return (0);
}
