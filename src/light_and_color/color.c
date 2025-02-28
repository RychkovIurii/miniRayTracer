/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:30:21 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 16:56:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** This function sets the pattern for the object and identity matrix for the
** transformation
** @param a - color a
** @param b - color b
** @return pattern
*/
t_pattern	set_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix();
	return (pattern);
}

/*
** This function computes ambient light
** @param material - material of the object
** @param effective_color - color of the object
** @param base_color - base color of the object
** @return ambient light
*/
t_tuple	compute_ambient(
	t_material material, t_tuple effective_color, t_tuple base_color)
{
	if (!is_tuples_equal(effective_color, create_color(0, 0, 0)))
		return (multiply_tuple_scalar(effective_color, material.ambient));
	return (multiply_tuple_scalar(base_color, material.ambient));
}

/*
** This function computes the specular light
** @param material - material of the object
** @param lightv - light vector
** @param comps - intersection
** @param light - light source
** @return specular light
*/
t_tuple	compute_specular(
	t_material material, t_tuple lightv, t_intersection comps, t_light light)
{
	t_tuple	reflectv;
	double	factor;
	double	reflect_dot_eye;

	reflectv = reflect(negate_tuple(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		return (create_color(0, 0, 0));
	factor = pow(reflect_dot_eye, material.shininess);
	return (multiply_tuple_scalar(light.intensity, material.specular * factor));
}

/*
** This function computes the lighting
** @param comps - intersection
** @param shape - shape
** @param light - light source
** @param in_shadow - is the object in shadow
** @return color
*/
t_tuple	lighting(
	t_intersection comps, t_shape shape, t_light light, int in_shadow)
{
	t_color	this;
	t_tuple	color;
	t_tuple	effective_color;
	t_tuple	lightv;
	double	light_dot_normal;

	if (comps.object->material.has_pattern)
		color = pattern_at_object(
				comps.object->material.pattern, shape, comps.over_point);
	else
		color = comps.object->material.color;
	effective_color = multiply_color(color, light.intensity);
	this.ambient = compute_ambient(
			comps.object->material, effective_color, color);
	if (in_shadow)
		return (this.ambient);
	lightv = normalize(substract_tuple(light.position, comps.over_point));
	light_dot_normal = dot(lightv, comps.normalv);
	if (light_dot_normal < 0)
		return (this.ambient);
	this.diffuse = multiply_tuple_scalar(effective_color,
			(comps.object->material.diffuse * light_dot_normal));
	this.specular = compute_specular(
			comps.object->material, lightv, comps, light);
	return (add_tuple(add_tuple(this.ambient, this.diffuse), this.specular));
}

/*
** This function computes the color of the object
** @param world - scene
** @param ray - ray
** @param remaining - remaining reflections
** @return color
*/
t_tuple	color_at(t_scene *world, t_ray ray, int remaining)
{
	t_intersects	xs;
	t_intersection	*hits;
	t_intersection	comps;
	t_tuple			color;

	xs = intersect_scene(world, ray);
	if (xs.count == 0)
	{
		free(xs.array);
		return (create_color(0, 0, 0));
	}
	hits = hit(xs);
	if (hits == NULL)
	{
		free(xs.array);
		return (create_color(0, 0, 0));
	}
	comps = prepare_computations(*hits, ray, &xs);
	color = shade_hit(world, comps, remaining, &xs);
	free(xs.array);
	return (color);
}
