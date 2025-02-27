/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:30:21 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:27:57 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_pattern	set_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix();
	return (pattern);
}

t_tuple	lighting(t_material material, t_shape shape, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv, int in_shadow)
{
	t_tuple	color;
	t_tuple	effective_color;
	t_tuple	lightv;
	t_tuple	reflectv;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	double	reflect_dot_eye;
	double	light_dot_normal;
	double	factor;

	if (material.has_pattern)
		color = pattern_at_object(material.pattern, shape, position);
	else
		color = material.color;
	effective_color = multiply_color(color, light.intensity);
	lightv = normalize(substract_tuple(light.position, position));
	//ambient = multiply_tuple_scalar(effective_color, material.ambient);
	if (!is_tuples_equal(effective_color, create_color(0, 0, 0)))
		ambient = multiply_tuple_scalar(effective_color, material.ambient);
	else
		ambient = multiply_tuple_scalar(color, material.ambient);
	light_dot_normal = dot(lightv, normalv);
	if (light_dot_normal < 0 || in_shadow)
	{
		diffuse = create_color(0, 0, 0);
		specular = create_color(0, 0, 0);
	}
	else
	{
		diffuse = multiply_tuple_scalar (effective_color, (material.diffuse * light_dot_normal));
		reflectv = reflect(negate_tuple(lightv), normalv);
		reflect_dot_eye = dot(reflectv, eyeview);
		if (reflect_dot_eye <= 0)
			specular = create_color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			specular = multiply_tuple_scalar(light.intensity, material.specular * factor);
		}
	}
	return (add_tuple(add_tuple(ambient, diffuse), specular));
}

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
