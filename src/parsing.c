/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:25 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/13 20:35:55 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	read_file(t_rt *rt, int fd)
{
	char *line;

	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
	}	
}

int	open_file(t_rt *rt)
{
	int	fd;

	fd = open(rt->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("File cannot be opened");
		return (1);
	}
	if (read_and_parse_line(rt, fd))
		return (1);
	return (0);
}

/*
int	validate_file(t_rt *rt)
{
	int	i;

	i = 0;
	
} */

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
- sphere
- plane
- cylinder
- cone?
- add to scene
*/