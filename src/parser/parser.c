/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/06 21:14:49 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <fcntl.h>

static char	**read_file_lines(int fd, int count)
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
		if (line[0] != '\0' && line[0] != '\n' && line[0] != '#')
			lines[i++] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static char	**read_file(t_rt *rt, int fd)
{
	char	**lines;

	rt->element_count = count_lines_in_file(fd);
	close(fd);
	if (rt->element_count == 0)
		return (NULL);
	fd = open(rt->filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Could not open file");
		return (NULL);
	}
	lines = read_file_lines(fd, rt->element_count);
	if (lines && counter(lines) != rt->element_count)
	{
		free_array(lines);
		lines = NULL;
	}
	return (lines);
}

static int	parse_line(char *line, t_rt *rt)
{
	char	*trimmed;
	char	**element;
	int		status;

	trimmed = trim_extra_spaces(line);
	if (!trimmed)
		return (error("Failed to trim line", 1));
	element = ft_split(trimmed, ' ');
	free(trimmed);
	if (!element)
		return (error("Failed to split line", 1));
	status = parse_element(element, rt);
	if (status)
	{
		ft_putstr_fd("Failed to parse line ", 2);
		ft_putstr_fd(line, 2);
		if (line[ft_strlen(line) - 1] != '\n')
			(void)write(2, "\n", 1);
	}
	free_array(element);
	return (status);
}

static int	parse_file_lines(char **lines, t_rt *rt)
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
		return (error("Could not open file", 1));
	lines = read_file(rt, fd);
	if (!lines)
		return (error("Failed to read file", 1));
	if (init_scene_structs(lines, rt) || parse_file_lines(lines, rt))
		return (free_and_return(NULL, lines, 1));
	free_array(lines);
	if (invalid_file_content(rt))
	{
		ft_putendl_fd("Invalid file content", 2);
		return (1);
	}
	return (0);
}
