/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:40:33 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 14:41:28 by irychkov         ###   ########.fr       */
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
