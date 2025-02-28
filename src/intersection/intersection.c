/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 12:06:34 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Frees the memory allocated for the intersections array
*/
void	free_intersects(t_intersects *xs)
{
	if (xs->array)
		free(xs->array);
	xs->array = NULL;
	xs->count = 0;
}

/*
** Sorts the intersections array by the t value
*/
void	insertion_sort_intersections(t_intersection *array, int count)
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
** Counts the total number of intersections in the scene
** We need this to allocate the right amount of memory
** for the intersections array
*/
int	count_total_intersections(t_scene *world, t_ray ray)
{
	int				i;
	int				total;
	t_intersects	temp;

	i = 0;
	total = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		total += temp.count;
		free_intersects(&temp);
		i++;
	}
	return (total);
}

/*
** Fills the intersections array with the intersections from
** all the shapes in the scene
*/
void	fill_intersections(t_scene *world, t_ray ray,
		t_intersection *xs_array, int total)
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
}

/*
** Returns the intersection of the ray with the scene
*/
t_intersects	intersect_scene(t_scene *world, t_ray ray)
{
	t_intersects	xs;
	t_intersection	*xs_array;
	int				total_intersections;

	xs_array = NULL;
	ft_bzero(&xs, sizeof(t_intersects));
	total_intersections = count_total_intersections(world, ray);
	if (total_intersections > 0)
	{
		xs_array = malloc(sizeof(t_intersection) * total_intersections);
		if (!xs_array)
			exit(1); //Think about error handling (free everything and exit)
		fill_intersections(world, ray, xs_array, total_intersections);
		insertion_sort_intersections(xs_array, total_intersections);
	}
	xs.count = total_intersections;
	xs.array = xs_array;
	return (xs);
}
