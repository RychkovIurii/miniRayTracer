/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 16:19:19 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Frees the memory allocated for the intersections array
*/
static void	free_intersects(t_intersects *xs)
{
	if (xs->array)
		free(xs->array);
	xs->array = NULL;
	xs->count = 0;
}

/*
** Sorts the intersections array by the t value
*/
static void	insertion_sort_intersections(t_intersection *array, int count)
{
	t_intersection	key;
	int				i;
	int				j;

	i = 1;
	while (i < count)
	{
		key = array[i];
		j = i - 1;
		if (array[j].t <= key.t)
		{
			i++;
			continue ;
		}
		while (j >= 0 && array[j].t > key.t)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
		i++;
	}
}

/*
** Fills the intersections array with the intersections from
** all the shapes in the scene
*/
static int	fill_intersections(
	t_scene *world, t_ray ray, t_intersection *xs_array)
{
	int				i;
	int				index;
	t_intersects	temp;

	i = 0;
	index = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		if (temp.count > 0)
		{
			ft_memcpy(xs_array + index, temp.array,
				sizeof(t_intersection) * temp.count);
			index += temp.count;
		}
		free_intersects(&temp);
		i++;
	}
	return (index);
}

/*
** Returns the intersection of the ray with the scene
*/
t_intersects	intersect_scene(t_scene *world, t_ray ray)
{
	t_intersects	xs;
	t_intersection	*xs_array;
	int				index;

	xs_array = NULL;
	ft_bzero(&xs, sizeof(t_intersects));
	xs_array = malloc(sizeof(t_intersection) * world->shape_count * 4);
	if (!xs_array)
		exit(1); //Think about error handling (free everything and exit)
	index = fill_intersections(world, ray, xs_array);
	insertion_sort_intersections(xs_array, index);
	xs.count = index;
	xs.array = xs_array;
	return (xs);
}
