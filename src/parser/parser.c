/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 16:28:48 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
	size_t	len;

	trimmed = trim_extra_spaces(line);
	if (!trimmed)
		error("Failed to trim line", 1);
	element = ft_split(trimmed, ' ');
	free(trimmed);
	if (!element)
		error("Failed to split line", 1);
	status = parse_element(element, rt);
	if (status)
	{
		ft_putendl_fd("Failed to parse line", 2);
		ft_putendl_fd(line, 2);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] != '\n')
			write(2, "\n", 1);
	}
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
		error("Could not open file", 1);
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
	print_parsed_content(rt);
	return (0);
}
