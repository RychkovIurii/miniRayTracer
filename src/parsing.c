/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/16 22:17:51 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	trim_extra_spaces(char *line)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			line[j++] = line[i];
			flag = 0;
		}
		else if (line[i] == ' ' && flag == 0)
		{
			line[j++] = line[i];
			flag = 1;
		}
		i++;
	}
	line[j] = '\0';
	//should trailing space be removed??
}

int	validate_element_data(char **element_data, t_rt *rt)
{
	int	i;

	if (check_identifier(element_data[0][0], rt))
		return (1);
	if (check_values()
	return (0);
}

int	count_lines_in_file(int fd)
{
	int	line_count;
	char	*line;

	line_count = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\0' && ft_strlen(line) > 0  && line[0] != '\n')
			line_count++;
		free(line);
	}
	return (line_count);
}

char	**read_file(t_rt rt, int fd)
{
	int		line_count;
	char	**lines;
	char	*line;
	int		i;
	
	line_count = count_lines_in_file(fd);
	close(fd);
	if (line_count <= 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(rt.filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[i] != '\0' && ft_strlen(line) > 0 && line[0] != '\n')
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
	char	**element_data;
	int		i;

	fd = open(rt->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	lines = read_file(*rt, fd);
	i = 0;
	while (lines[i])
	{
		trim_extra_spaces(lines[i]);
		printf("Line %s", lines[i]);
		element_data = ft_split(lines[i], ' ');
		if (!element_data)
		{
			printf("Failed to split line into elements\n");
			break ;
		}
		print_elements(element_data);
		if (!validate_elements(element_data, rt))
		{
			free_elements(element_data);
			return (1);
		}	
		free_elements(element_data); 
		i++;
	}
	free_elements(lines);
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