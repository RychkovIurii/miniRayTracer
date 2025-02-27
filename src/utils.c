/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:04:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 18:55:32 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	count_non_shape_elements(char **lines)
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

int	init_scene_structs(char **lines, t_rt *rt)
{
	int	non_shape;

	rt->scene = ft_calloc(1, sizeof(t_scene));
	if (!rt->scene)
	{
		print_error("Failed to allocate t_scene");
		return (1);
	}
	non_shape = count_non_shape_elements(lines);
	rt->scene->shape_count = 0;
	rt->scene->needs_render = 1;
	rt->scene->shapes = ft_calloc(rt->element_count - non_shape, sizeof(t_shape));
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