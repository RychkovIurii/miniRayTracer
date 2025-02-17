/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:04:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/17 20:25:45 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	free_array(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void print_elements(char **elements)
{
	int	i;

	i = 0;
	while (elements[i])
	{
		printf("%s\n", elements[i]);
		i++;
	}
}

int	allocate_and_init_scene(t_rt *rt)
{
	rt->scene = malloc(sizeof(t_scene));
	if (!rt->scene)
	{
		print_error("Failed to allocate t_scene");
		return (1);
	}
	ft_memset(rt->scene, 0, sizeof(t_scene));
	return (0);
}

int	allocate_and_init_camera(t_rt *rt)
{
	rt->scene->camera = malloc(sizeof(t_camera));
	if (!rt->scene->camera)
	{
		print_error("Failed to allocate t_camera");
		return (1);
	}
	free(rt->scene);
	ft_memset(rt->scene->camera, 0, sizeof(t_camera));
	return (0);
}
