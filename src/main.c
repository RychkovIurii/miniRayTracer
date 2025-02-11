/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:21:20 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/11 18:36:53 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	main(int argc, char **argv)
{
	t_rt	rt;
	
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if 

		//validate file
	//init_scene
	//setup_window
	//key_hook ??
	//mlx_loop
}

int	validate_file_ext(t_rt *rt)
{
	const char	*filename;
	const char	*dot;

	filename = rt->filename;
	dot = ft_strrchr(filename, '.');
	if(!dot)
		return(1);
	if (ft_strncmp(dot, ".rt\0", 4))
		return (1);
	return (0);
}

void	initialize_structs(char **argv, t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	rt->filename = argv[1];
	if (validate_file_ext(rt))
	{
		printf("Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
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
- sphere
- plane
- cylinder
- cone?
- add to scene
*/