/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:58 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/05 13:41:21 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_and_cleanup(t_rt *rt)
{
	ft_putendl_fd("Rendering error", 2);
	mlx_close_window(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	free_pixels(rt->scene->pixels, rt->scene->height);
	free_rt(rt);
	exit(1);
}

void	exit_and_cleanup_with_xs(t_rt *rt, t_intersection *xs_array)
{
	ft_putendl_fd("Rendering error", 2);
	free(xs_array);
	mlx_close_window(rt->scene->mlx);
	mlx_terminate(rt->scene->mlx);
	free_pixels(rt->scene->pixels, rt->scene->height);
	free_rt(rt);
	exit(1);
}

int	free_and_return(t_rt *rt, char **array, int ret)
{
	if (array)
		free_array(array);
	free_rt(rt);
	return (ret);
}

void	free_arrays(char **array1, char **array2)
{
	if (array1)
	{
		free_array(array1);
		*array1 = NULL;
	}
	if (array2)
	{
		free_array(array2);
		*array2 = NULL;
	}
}
