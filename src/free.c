/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:52:11 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/06 20:58:43 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	free_pixels_back(t_tuple **pixels, int i)
{
	while (i > 0)
	{
		i--;
		free(pixels[i]);
	}
	free(pixels);
	return (1);
}

void	free_pixels(t_tuple **pixels, int height)
{
	int	i;

	i = 0;
	if (!pixels)
		return ;
	while (i < height)
		free(pixels[i++]);
	free(pixels);
}

void	free_rt(t_rt *rt)
{
	if (!rt)
		return ;
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

int	free_pixels_and_rt(t_rt *rt, int ret, char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	free_pixels(rt->scene->pixels, rt->scene->height);
	free_rt(rt);
	return (ret);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
