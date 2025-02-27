/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_and_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:27:31 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 16:31:37 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Checks for intersections between a ray and a sphere.
** The function calculates the intersection points with the sphere's surface.
** @param sphere: The sphere being tested for intersection.
** @param ray: The ray being tested for intersection.
** @returns A t_intersects struct containing up to two valid intersection points.
*/
t_intersects	local_intersect_sphere(t_shape *sphere, t_ray transformed_ray)
{
	t_intersects	result;
	t_tuple			sphere_to_ray;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			sqrt_d;

	ft_bzero(&result, sizeof(t_intersects));
	sphere_to_ray = vector(
			transformed_ray.origin.x, transformed_ray.origin.y,
			transformed_ray.origin.z);
	a = dot(transformed_ray.direction, transformed_ray.direction);
	b = 2 * dot(transformed_ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (result);
	sqrt_d = sqrt(discriminant);
	result.count = 2;
	result.array = malloc(sizeof(t_intersection) * 2);
	result.array[0].t = (-b - sqrt_d) / (2 * a);
	result.array[0].object = sphere;
	result.array[1].t = (-b + sqrt_d) / (2 * a);
	result.array[1].object = sphere;
	return (result);
}

/*
** Checks for intersections between a ray and a plane.
** The function calculates the intersection point with the plane's surface.
** @param plane: The plane being tested for intersection.
** @param ray: The ray being tested for intersection.
** @returns A t_intersects struct containing one valid intersection point.
*/
t_intersects	local_intersect_plane(t_shape *plane, t_ray transformed_ray)
{
	t_intersects	result;

	ft_bzero(&result, sizeof(t_intersects));
	if (fabs(transformed_ray.direction.y) < EPSILON)
		return (result);
	result.count = 1;
	result.array = malloc(sizeof(t_intersection));
	result.array[0].t = -transformed_ray.origin.y / transformed_ray.direction.y;
	result.array[0].object = plane;
	return (result);
}
