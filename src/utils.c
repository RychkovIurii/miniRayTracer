/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:04:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/19 10:31:40 by henbuska         ###   ########.fr       */
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

int	init_scene_structs(t_rt *rt)
{
	rt->scene = calloc(1, sizeof(t_scene));
	if (!rt->scene)
	{
		print_error("Failed to allocate t_scene");
		return (1);
	}
	rt->scene->shape_count = 0;
	rt->scene->shapes = calloc(rt->element_count - 2, sizeof(t_shape));
	if (!rt->scene->shapes)
	{
		print_error("Failed to allocate shapes array");
		return (1);
	}
	return (0);
}

int	error(char *message, int ret)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (ret);
}

void	free_rt(t_rt *rt)
{
	if (!rt)
		return;
	if (rt->scene)
	{
		if (rt->scene->shapes)
		{
			free(rt->scene->shapes);
		}
		free(rt->scene);
	}
	free(rt);
}

int	ft_strcmp(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && (s1[i] == s2[i]))
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}