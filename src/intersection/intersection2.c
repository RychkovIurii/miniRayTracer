/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:59:31 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/04 15:54:31 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**	Checks if the intersection is valid
**	@return the first closest valid intersection
*/
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

/*
**	Checks if the ray intersects the shape
**	@return the intersection
*/
t_intersects	intersect(t_shape *shape, t_ray ray, t_intersection *xs_array,
		t_scene *world)
{
	t_ray			local_ray;
	t_intersects	empty;

	ft_bzero(&empty, sizeof(t_intersects));
	local_ray = transform_ray(ray, shape->transform_inv);
	if (shape->type == SHAPE_SPHERE)
		return (local_intersect_sphere(shape, local_ray, xs_array, world));
	else if (shape->type == SHAPE_PLANE)
		return (local_intersect_plane(shape, local_ray, xs_array, world));
	else if (shape->type == SHAPE_CYLINDER)
		return (local_intersect_cylinder(shape, local_ray, xs_array, world));
	else if (shape->type == SHAPE_CONE)
		return (local_intersect_cone(shape, local_ray, xs_array, world));
	return (empty);
}
