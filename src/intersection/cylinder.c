/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:20:14 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 16:25:31 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Checks whether a ray intersects with the cylinder's cap.
 - The function calculates the intersection point's (x, z) coordinates and 
   verifies if they lie within the cap's radius.
 - @param cyl: The cylinder being tested for intersection.
 - @param ray: The ray being tested for intersection.
 - @param t: The parametric distance along the ray to the intersection.
 - @returns 1 if the intersection is within the cap's radius, 0 otherwise.
 */
int	check_cylinder_cap(t_shape cyl, t_ray ray, double t)
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
 - If the cylinder is closed, the function calculates the intersection points
   with the top and bottom caps.
 - @param cyl: The cylinder being tested for intersection.
 - @param ray: The ray being tested for intersection.
 - @param result: The intersection array that will store valid intersections.
 - @returns The updated result containing any intersection with the caps.
 */
t_intersects	intersect_cylinder_caps(t_shape *cyl, t_ray ray, t_intersects result)
{
	double	t;

	t = (cyl->min - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[2].t = t;
		result.count = 3;
		result.array[2].object = cyl;
	}
	t = (cyl->max - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[3].t = t;
		result.count = 4;
		result.array[3].object = cyl;
	}
	return (result);
}
/*
** Checks for intersections between a ray and a cylinder.
** The function calculates the intersection points with the cylinder's curved
** surface and its caps if the cylinder is closed.
** @param cylinder: The cylinder being tested for intersections.
** @param ray: The ray being tested for intersection.
** @returns A t_intersects struct containing up to four valid intersection points.
*/
t_intersects	local_intersect_cylinder(t_shape *cylinder, t_ray ray)
{
	t_intersects	result;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			sqrt_discriminant;
	double			temp;
	double			y0;
	double			y1;
	double			t0;
	double			t1;
	int				count;
	
	result.count = 0;
	result.array = ft_calloc(4, sizeof(t_intersection));
	if (!result.array)
		return (result);
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	if (fabs(a) > EPSILON)
	{
		b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
		c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - cylinder->radius * cylinder->radius;
		discriminant = b * b - 4 * a * c;
		if (discriminant >= 0)
		{
			sqrt_discriminant = sqrt(discriminant);
			t0 = (-b - sqrt_discriminant) / (2 * a);
			t1 = (-b + sqrt_discriminant) / (2 * a);
			y0 = ray.origin.y + t0 * ray.direction.y;
			if (cylinder->min < y0 && y0 < cylinder->max)
			{
				result.array[0].t = t0;
				result.count = 1;
				result.array[0].object = cylinder;
			}
			y1 = ray.origin.y + t1 * ray.direction.y;
			if (cylinder->min < y1 && y1 < cylinder->max)
			{
				result.array[1].t = t1;
				result.count = 2;
				result.array[1].object = cylinder;
			}
		}
	}
	if (cylinder->closed == 1 && fabs(ray.direction.y) > EPSILON)
		result = intersect_cylinder_caps(cylinder, ray, result);
	return (result);
}
