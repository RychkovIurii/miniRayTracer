/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:21:20 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/13 13:10:18 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"


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
		free(rt);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		exit(EXIT_FAILURE);
	initialize_structs(argv, rt);
	return (0);
		
	//validate file
	//init_scene
	//setup_window
	//key_hook ??
	//mlx_loop
}



/*int	open_file(t_rt *rt)
{
	int	fd;

	fd = open(rt->filename, O_RDONLY);
	if (fd == -1)
	{
		printf("File cannot be opened");
		return (1);
	}
	
}

int	validate_file(t_rt *rt)
{
	int	i;

	i = 0;
	
} */