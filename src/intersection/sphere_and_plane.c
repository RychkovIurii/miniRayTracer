/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_and_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:27:31 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 16:41:05 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Calculates the quadratic coefficients for a ray and a sphere.
*/
static t_quadratic	compute_quadratic_sphere(
	t_ray transformed_ray, t_shape *shape)
{
	t_quadratic	q;
	t_tuple		sphere_to_ray;

	sphere_to_ray = vector(
			transformed_ray.origin.x, transformed_ray.origin.y,
			transformed_ray.origin.z);
	q.a = dot(transformed_ray.direction, transformed_ray.direction);
	q.b = 2 * dot(transformed_ray.direction, sphere_to_ray);
	q.c = dot(sphere_to_ray, sphere_to_ray) - shape->radius * shape->radius;
	return (q);
}

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
	t_quadratic		q;
	double			discriminant;
	double			sqrt_d;

	ft_bzero(&result, sizeof(t_intersects));
	q = compute_quadratic_sphere(transformed_ray, sphere);
	discriminant = q.b * q.b - 4 * q.a * q.c;
	if (discriminant < 0)
		return (result);
	sqrt_d = sqrt(discriminant);
	result.count = 2;
	result.array = malloc(sizeof(t_intersection) * 2); // Error handling
	result.array[0].t = (-q.b - sqrt_d) / (2 * q.a);
	result.array[0].object = sphere;
	result.array[1].t = (-q.b + sqrt_d) / (2 * q.a);
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
	result.array = malloc(sizeof(t_intersection)); // Error handling
	result.array[0].t = -transformed_ray.origin.y / transformed_ray.direction.y;
	result.array[0].object = plane;
	return (result);
}
