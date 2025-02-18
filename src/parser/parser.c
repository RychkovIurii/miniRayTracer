/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/18 19:12:44 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	**read_file(t_rt *rt, int fd)
{
	char	**lines;
	char	*line;
	int		i;
	
	rt->element_count = count_lines_in_file(fd);
	close(fd);
	if (rt->element_count <= 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (rt->element_count + 1));
	if (!lines)
		return (NULL);
	fd = open(rt->filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\0' && ft_strlen(line) > 0 && line[0] != '\n')
			lines[i++] = line;
		else
			free(line);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	parse_file(t_rt *rt)
{
	int		fd;
	char	**lines;
	char	**element;
	int		i;
	char	*trimmed;

	fd = open(rt->filename, O_RDONLY);
	if (fd == -1)
	{
		print_error("Could not open file");
		return (1);
	}
	lines = read_file(rt, fd);
	if (!lines)
		return (1);
	i = 0;
	while (lines[i])
	{
		trimmed = trim_extra_spaces(lines[i]);
		if (!trimmed)
		{
			free_array(lines);
			free_rt(rt);
			return (1);
		}
		element = ft_split(trimmed, ' ');
		if (!element)
		{
			printf("Failed to split line into tokens\n");
			free_array(lines);
			free_rt(rt);
			return (1);
		}
		print_elements(element);
		if (init_scene_structs(rt))
		{
			free_rt(rt);
			return (1);
		}
		if (parse_element(element, rt))
		{
			free_array(lines);
			free_array(element);
			free_rt(rt);
			return (1);
		}	
		free_array(element); 
		i++;
	}
	free_array(lines);
	return (0);
}

/* Parse file
 - validate file extension
 - check access and permissions
 - open file
 - read file with get_next_line
*/

/* Parse ambient
 - ratio
 - color
 - add to scene
*/

/* Parse camera
 - coordinates of view point
 - orientation vector
 - field of view
 - add to scene
*/

/* Parse light
 - coordination of light point
 - brightness ration
 - RGB color
 - add to scene
*/

/* Parse objects
- create shape
- sphere
- plane
- cylinder
- cone?
- add to scene
*/