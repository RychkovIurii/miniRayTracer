/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/14 17:24:33 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	validate_elements(char **elements, t_rt *rt)
{
	int	i;

	if (check_identifier(elements[0][0], rt))
	{
		printf("Invalid identifier\n");
		return (1);
	}
	return (0);
}

void	parse_file(t_rt *rt)
{
	int		fd;
	char	*line;
	char	**elements;

	fd = open(rt->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return ;
	}
	while((line = get_next_line(fd)) != NULL)
	{
		if (ft_strlen(line) == 0 || !line)
		{
			free(line);
			continue ;
		}
		elements = ft_split(line, ' ');
		if (!elements)
		{
			free(line);
			return ;
		}
		print_elements(elements);
		if (!validate_elements(elements, rt))
		{
			printf("Invalid line format\n");
		}
		free_elements(elements);
		free(line);
	}
	close(fd);
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