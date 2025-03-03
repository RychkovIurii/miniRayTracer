/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:52:11 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 18:52:53 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_pixels(t_tuple **pixels, int height)
{
	if (!pixels)
		return;
	for (int i = 0; i < height; i++)
	{
		free(pixels[i]);
	}
	free(pixels);
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
