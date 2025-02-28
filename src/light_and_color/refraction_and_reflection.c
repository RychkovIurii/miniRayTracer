/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_and_reflection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:01:18 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 16:04:34 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** The function calculates the color of the reflected ray at the intersection.
** The function takes the world, the intersection, and the remaining number
** of reflections as parameters.
** @returns t_tuple The color of the reflected ray at the intersection.
*/
t_tuple	reflected_color(t_scene *world, t_intersection comps, int remaining)
{
	t_tuple	color;
	t_tuple	reflect_color;

	if (remaining <= 0)
		return (create_color(0, 0, 0));
	if (comps.object->material.reflective <= EPSILON)
		return (create_color(0, 0, 0));
	color = color_at(world,
			create_ray(comps.over_point, comps.reflectv), remaining - 1);
	reflect_color = multiply_tuple_scalar(
			color, comps.object->material.reflective);
	return (reflect_color);
}

/*
** The function calculates the color of the refracted ray at the intersection.
** The function takes the world, the intersection, and the remaining number
** of reflections as parameters.
** @returns t_tuple The color of the refracted ray at the intersection.
*/
t_tuple	refracted_color(t_scene *world, t_intersection comps, int remaining)
{
	t_tuple	refract_color;
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	t_tuple	direction;

	if (remaining <= 0 || comps.object->material.transparency < EPSILON)
		return (create_color(0, 0, 0));
	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.eyev, comps.normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (create_color(0, 0, 0));
	direction = substract_tuple(
			multiply_tuple_scalar(
				comps.normalv, n_ratio * cos_i - sqrt(1.0 - sin2_t)),
			multiply_tuple_scalar(comps.eyev, n_ratio));
	refract_color = color_at(world, create_ray(
				comps.under_point, direction), remaining - 1);
	return (multiply_tuple_scalar(
			refract_color, comps.object->material.transparency));
}

/*
** The function uses Schlick's approximation to compute the reflectance.
** It is based on the Fresnel equations, which describe the behavior of light
** when it moves between two media.
** The function takes the intersection as a parameter and returns the reflectance
** at the intersection.
** The reflectance is a value between 0 and 1, where 0 means no reflection
** and 1 means full reflection.
** @returns double The reflectance at the intersection.
*/
double	schlick(t_intersection comps)
{
	double	cos;
	double	n_ratio;
	double	sin2_t;
	double	r0;

	cos = dot(comps.eyev, comps.normalv);
	if (comps.n1 > comps.n2)
	{
		n_ratio = comps.n1 / comps.n2;
		sin2_t = n_ratio * n_ratio * (1 - cos * cos);
		if (sin2_t > 1.0)
			return (1.0);
		cos = sqrt(1.0 - sin2_t);
	}
	r0 = (comps.n1 - comps.n2) / (comps.n1 + comps.n2);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow(1 - cos, 5));
}

/*
** The function checks if the point is in the shadow.
** The function takes the world and the point as parameters.
** @returns int 1 if the point is in the shadow, 0 otherwise.
*/
int	is_shadowed(t_scene world, t_tuple point)
{
	t_ray			r;
	t_tuple			v;
	t_intersects	xs;
	t_intersection	*hit_obj;

	v = substract_tuple(world.light.position, point);
	r = create_ray(point, normalize(v));
	xs = intersect_scene(&world, r);
	if (xs.count == 0)
	{
		free(xs.array);
		return (0);
	}
	hit_obj = hit(xs);
	if (hit_obj && hit_obj->t < magnitude(v))
	{
		free(xs.array);
		return (1);
	}
	free(xs.array);
	return (0);
}

/* The function ought to return the color at the intersection encapsulated
** by comps, in the given world.
** P.S. If we have more than one light source, we will have to loop through
** all of them and sum the results.
** @param world: t_scene The world.
** @param comps: t_intersection The intersection.
** @param remaining: int The number of remaining reflections.
** @param xs: t_intersects The intersections.
** @returns t_tuple The color at the intersection.
*/
t_tuple	shade_hit(t_scene *world, t_intersection comps, int remaining,
	t_intersects *xs)
{
	t_tuple	color;
	t_tuple	surface;
	t_tuple	reflected;
	t_tuple	refracted;
	double	reflectance;

	surface = lighting(comps, *comps.object, world->light,
			is_shadowed(*world, comps.over_point));
	reflected = reflected_color(world, comps, remaining);
	refracted = refracted_color(world, comps, remaining);
	if (comps.object->material.transparency > EPSILON
		&& comps.object->material.reflective > EPSILON)
	{
		reflectance = schlick(comps);
		color = add_tuple(surface,
				add_tuple(multiply_tuple_scalar(reflected, reflectance),
					multiply_tuple_scalar(refracted, 1.0 - reflectance)));
	}
	else if (comps.object->material.transparency > EPSILON)
		color = add_tuple(surface, refracted);
	else
		color = add_tuple(surface, reflected);
	return (color);
}
