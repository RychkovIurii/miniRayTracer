/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:15:09 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:20:36 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* 
Checks whether a ray intersects with the cone's cap. 
The function calculates the intersection point's (x, z) coordinates and 
verifies if they lie within the cap's radius at the given height.

@param ray: The ray being tested for intersection.
@param t: The parametric distance along the ray to the intersection.
@param cone: The cone being tested for intersection.
@param y: The y-coordinate of the cap (either min or max of the cone).
@returns 1 if the intersection is within the cap's radius, 0 otherwise.
*/
int	check_cone_cap(t_ray ray, double t, t_shape cone, double y)
{
	double	x;
	double	z;
	double	cap_radius;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if (fabs(cone.height) < EPSILON)
		return (0);
	cap_radius = cone.radius * fabs(y - cone.max) / cone.height;
	return ((x * x) + (z * z) <= cap_radius * cap_radius);
}

/* 
Checks for intersections between a ray and the cone's caps.
If the cone is closed and the ray is not parallel to the y-axis, 
it calculates possible intersection with bottom cap.

@param cone: The cone being tested for intersections.
@param ray: The ray being tested for intersection.
@param result: The intersection array that will store valid intersections.
@returns The updated result containing any intersection with the cap.
*/
t_intersects	intersect_cone_caps(t_shape *cone, t_ray ray, t_intersects result)
{
	double	t;

	if (cone->closed && fabs(ray.direction.y) > EPSILON)
	{
		t = (cone->min - ray.origin.y) / ray.direction.y;
		if (check_cone_cap(ray, t, *cone, cone->min))
		{
			result.array[2].t = t;
			result.count = 3;
			result.array[2].object = cone;
		}
	}
	return (result);
}

/* 
Computes the intersections between a ray and a truncated cone.
It first checks for intersections with the cone's curved surface using the quadratic equation.
Then, it filters valid intersections within the truncated height range.
Finally, it checks for intersections with the cone's cap.

@param cone: The cone being tested for intersection.
@param ray: The ray being tested for intersection.
@returns A t_intersects struct containing up to three valid intersection points.
*/
t_intersects	local_intersect_cone(t_shape *cone, t_ray ray)
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
	double			slope;
	double			slope2;

	result.count = 0;
	result.array = ft_calloc(3, sizeof(t_intersection));
	if (!result.array)
		return (result);
	slope = cone->radius / cone->height;
	slope2 = slope * slope;
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2) - slope2 * pow(ray.direction.y, 2);
	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z - slope2 * ray.origin.y * ray.direction.y);
	c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - slope2 * ray.origin.y * ray.origin.y;
	if (fabs(a) < EPSILON)
	{
		if (fabs(b) < EPSILON)
			return (result);
		t0 = -c / b;
		y0 = ray.origin.y + t0 * ray.direction.y;
		if (cone->min < y0 && y0 < cone->max)
		{
			result.array[0].t = t0;
			result.count = 1;
			result.array[0].object = cone;
		}
		return (result);
	}
	else
	{
		discriminant = b * b - 4 * a * c;
		if (discriminant >= 0)
		{
			sqrt_discriminant = sqrt(discriminant);
			t0 = (-b - sqrt_discriminant) / (2 * a);
			t1 = (-b + sqrt_discriminant) / (2 * a);
			y0 = ray.origin.y + t0 * ray.direction.y;
			if (cone->min < y0 && y0 < cone->max)
			{
				result.array[0].t = t0;
				result.count = 1;
				result.array[0].object = cone;
			}
			y1 = ray.origin.y + t1 * ray.direction.y;
			if (cone->min < y1 && y1 < cone->max)
			{
				result.array[1].t = t1;
				result.count = 2;
				result.array[1].object = cone;
			}
		}
	}
	result = intersect_cone_caps(cone, ray, result);
	return (result);
}
