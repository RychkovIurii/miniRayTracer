/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:43:18 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/05 13:44:25 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	count_lines_in_file(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0' && ft_strlen(line) > 0 && line[0] != '\n'
			&& line[0] != '#')
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

void	print_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
}

int	error(char *message, int ret)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (ret);
}

int	counter(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
