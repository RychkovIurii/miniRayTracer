/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:15:09 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 16:44:13 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* 
Checks for intersections between a ray and the cone's caps.
If the cone is closed and the ray is not parallel to the y-axis, 
it calculates possible intersection with bottom cap.

@param cone: The cone being tested for intersections.
@param ray: The ray being tested for intersection.
@param result: The intersection array that will store valid intersections.
@returns The updated result containing any intersection with the cap.
*/
static t_intersects	intersect_cone_caps(
		t_shape *cone, t_ray ray, t_intersects result)
{
	double	t;

	if (cone->closed && fabs(ray.direction.y) > EPSILON)
	{
		t = (cone->min - ray.origin.y) / ray.direction.y;
		if (check_cone_cap(ray, t, *cone, cone->min))
		{
			result.array[result.count].t = t;
			result.array[result.count++].object = cone;
		}
	}
	return (result);
}

static t_quadratic	compute_quadratic_cone(t_ray ray, t_shape *cone)
{
	t_quadratic	q;
	double		slope;
	double		slope2;

	slope = cone->radius / cone->height;
	slope2 = slope * slope;
	q.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z
		- slope2 * ray.direction.y * ray.direction.y;
	q.b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z
			- slope2 * ray.origin.y * ray.direction.y);
	q.c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z
		- slope2 * ray.origin.y * ray.origin.y;
	return (q);
}

static void	handle_quadratic_cone_intersection(t_ray ray, t_shape *cone,
	t_quadratic q, t_intersects *result)
{
	double	discriminant;
	double	sqrt_discriminant;
	t_tuple	p;

	discriminant = q.b * q.b - 4 * q.a * q.c;
	if (discriminant < 0)
		return ;
	sqrt_discriminant = sqrt(discriminant);
	p.x = (-q.b - sqrt_discriminant) / (2 * q.a);
	p.y = (-q.b + sqrt_discriminant) / (2 * q.a);
	p.z = ray.origin.y + p.x * ray.direction.y;
	if (cone->min < p.z && p.z < cone->max)
	{
		result->array[result->count].t = p.x;
		result->array[result->count++].object = cone;
	}
	p.w = ray.origin.y + p.y * ray.direction.y;
	if (cone->min < p.w && p.w < cone->max)
	{
		result->array[result->count].t = p.y;
		result->array[result->count++].object = cone;
	}
}

static void	handle_linear_cone_intersection(t_ray ray, t_shape *cone,
	t_quadratic q, t_intersects *result)
{
	double	t0;
	double	y0;

	if (fabs(q.b) < EPSILON)
		return ;
	t0 = -q.c / q.b;
	y0 = ray.origin.y + t0 * ray.direction.y;
	if (cone->min < y0 && y0 < cone->max)
	{
		result->array[result->count].t = t0;
		result->array[result->count++].object = cone;
	}
}

/* 
Computes the intersections between a ray and a truncated cone.
It first checks for intersections with the cone's curved surface using
the quadratic equation.
Then, it filters valid intersections within the truncated height range.
Finally, it checks for intersections with the cone's cap.

@param cone: The cone being tested for intersection.
@param ray: The ray being tested for intersection.
@returns A t_intersects struct containing up to three valid intersection points.
*/
t_intersects	local_intersect_cone(t_shape *cone, t_ray ray)
{
	t_intersects	result;
	t_quadratic		q;

	result.count = 0;
	result.array = ft_calloc(3, sizeof(t_intersection)); // Error handling
	if (!result.array)
		return (result);
	q = compute_quadratic_cone(ray, cone);
	if (fabs(q.a) < EPSILON)
	{
		handle_linear_cone_intersection(ray, cone, q, &result);
		return (result);
	}
	else
		handle_quadratic_cone_intersection(ray, cone, q, &result);
	result = intersect_cone_caps(cone, ray, result);
	return (result);
}
