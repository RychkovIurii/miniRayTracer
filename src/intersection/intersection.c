/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:23:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_intersects(t_intersects *xs)
{
	if (xs->array)
		free(xs->array);
	xs->array = NULL;
	xs->count = 0;
}

t_intersects	intersect(t_shape *shape, t_ray ray)
{
	t_ray			local_ray;
	t_intersects	empty;

	ft_bzero(&empty, sizeof(t_intersects));
	local_ray = transform_ray(ray, shape->transform_inv);
	if (shape->type == SHAPE_SPHERE)
		return (local_intersect_sphere(shape, local_ray));
	else if (shape->type == SHAPE_PLANE)
		return (local_intersect_plane(shape, local_ray));
	else if (shape->type == SHAPE_CYLINDER)
		return (local_intersect_cylinder(shape, local_ray));
	else if (shape->type == SHAPE_CONE)
		return (local_intersect_cone(shape, local_ray));
	return (empty);
}

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
			continue;
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

// Function to find the intersections in the world
t_intersects	intersect_scene(t_scene *world, t_ray ray)
{
	t_intersects	xs;
	t_intersects	temp;
	t_intersection	*xs_array;
	t_intersection	*temp_array;
	int total_intersections = 0;
	int i;
	int index;
	temp_array = NULL;

	// Allocate memory for intersections dynamically (in case there are more than 2 intersections)
	xs_array = NULL;

	// First pass: Count total intersections
	i = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		total_intersections += temp.count;
		free_intersects(&temp);
		i++;
	}
	//printf("Total intersections: %d\n", total_intersections);
	// Allocate memory once
	if (total_intersections > 0)
	{
		xs_array = malloc(sizeof(t_intersection) * total_intersections);
		if (!xs_array)
		{
			xs.count = 0;
			xs.array = NULL;
			return xs;
		}
	}

	// Second pass: Store all intersections
	index = 0;
	i = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		if (temp.count > 0)
		{
			ft_memcpy(xs_array + index, temp.array, sizeof(t_intersection) * temp.count);
			index += temp.count;
		}
		free_intersects(&temp);
		i++;
	}

	insertion_sort_intersections(xs_array, total_intersections);
	xs.count = total_intersections;
	xs.array = xs_array;
	return (xs);
}

t_intersection	*hit(t_intersects intersections)
{
	int	i;

	i = 0;
	while (i < intersections.count)
	{
		if (intersections.array[i].t > EPSILON)
			return (&intersections.array[i]);
		i++;
	}
	return (NULL);
}
