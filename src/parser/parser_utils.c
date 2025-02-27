/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:43:18 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 20:08:09 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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

void	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
}

int	free_and_return(t_rt *rt, char **array, int ret)
{
	free_array(array);
	free_rt(rt);
	return (ret);
}

int	print_clean(t_rt *rt, char *message, int ret)
{
	free_rt(rt);
	print_error("Invalid file content");
	return (ret);
}

void	free_arrays(char **array1, char **array2)
{
	if (array1)
	{
		free_array(array1);
		*array1 = NULL;
	}
	if (array2)
	{
		free_array(array2);
		*array2 = NULL;
	}
}
