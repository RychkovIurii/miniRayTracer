/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:20:14 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 16:29:12 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Checks whether a ray intersects with the cylinder's cap.
 - The function calculates the intersection point's (x, z) coordinates and 
 - verifies if they lie within the cap's radius.
 - @param cyl: The cylinder being tested for intersection.
 - @param ray: The ray being tested for intersection.
 - @param t: The parametric distance along the ray to the intersection.
 - @returns 1 if the intersection is within the cap's radius, 0 otherwise.
 */
static int	check_cylinder_cap(t_shape cyl, t_ray ray, double t)
{
	double	x;
	double	z;
	double	sum_of_squares;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	sum_of_squares = x * x + z * z;
	return (sum_of_squares <= cyl.radius * cyl.radius);
}

/* Checks cap intersectins (top and bottom)
 - If the cylinder is closed, the function calculates the intersection
 - points with the top and bottom caps.
 - @param cyl: The cylinder being tested for intersection.
 - @param ray: The ray being tested for intersection.
 - @param result: The intersection array that will store valid intersections.
 - @returns The updated result containing any intersection with the caps.
 */
static t_intersects	intersect_cylinder_caps(
		t_shape *cyl, t_ray ray, t_intersects result)
{
	int		count;
	double	t;

	count = result.count;
	t = (cyl->min - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[count].t = t;
		result.array[count++].object = cyl;
	}
	t = (cyl->max - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[count].t = t;
		result.array[count++].object = cyl;
	}
	result.count = count;
	return (result);
}

/*
** Calculates the quadratic coefficients for the cylinder intersection.
*/
static t_quadratic	compute_quadratic_cylinder(t_ray ray, t_shape *cylinder)
{
	t_quadratic	q;

	q.a = (ray.direction.x * ray.direction.x)
		+ (ray.direction.z * ray.direction.z);
	q.b = 2 * ray.origin.x * ray.direction.x
		+ 2 * ray.origin.z * ray.direction.z;
	q.c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z
		- cylinder->radius * cylinder->radius;
	return (q);
}

/*
** Calculates the intersection points with the cylinder's curved surface.
*/
static int	compute_intersections_cyl(t_ray ray, t_shape *cylinder,
	t_quadratic q, t_intersects *result)
{
	int		count;
	t_tuple	p;
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = q.b * q.b - 4 * q.a * q.c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	p.x = (-q.b - sqrt_discriminant) / (2 * q.a);
	p.y = (-q.b + sqrt_discriminant) / (2 * q.a);
	p.z = ray.origin.y + p.x * ray.direction.y;
	p.w = ray.origin.y + p.y * ray.direction.y;
	count = 0;
	if (cylinder->min < p.z && p.z < cylinder->max)
	{
		result->array[count].t = p.x;
		result->array[count++].object = cylinder;
	}
	if (cylinder->min < p.w && p.w < cylinder->max)
	{
		result->array[count].t = p.y;
		result->array[count++].object = cylinder;
	}
	return (count);
}

/*
** Checks for intersections between a ray and a cylinder.
** The function calculates the intersection points with the cylinder's
** curved surface and its caps if the cylinder is closed.
** @param cylinder: The cylinder being tested for intersections.
** @param ray: The ray being tested for intersection.
** @returns A t_intersects struct containing up to four valid
** intersection points.
*/
t_intersects	local_intersect_cylinder(t_shape *cylinder, t_ray ray)
{
	t_intersects	result;
	t_quadratic		q;

	result.count = 0;
	result.array = ft_calloc(4, sizeof(t_intersection));
	if (!result.array)
		return (result); // Error handling
	q = compute_quadratic_cylinder(ray, cylinder);
	if (fabs(q.a) > EPSILON)
	{
		result.count = compute_intersections_cyl(ray, cylinder, q, &result);
	}
	if (cylinder->closed == 1 && fabs(ray.direction.y) > EPSILON)
		result = intersect_cylinder_caps(cylinder, ray, result);
	return (result);
}
