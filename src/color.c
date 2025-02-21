/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:30:21 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/21 19:38:39 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple	stripe_at(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_tuple		gradient_at(t_pattern pattern, t_tuple point)
{
	t_tuple distance;
	double fraction;

	distance = substract_tuple(pattern.color_b, pattern.color_a);
	fraction = point.x - floor(point.x);
	return (add_tuple(pattern.color_a, multiply_tuple_scalar(distance, fraction)));
}

t_tuple		ring_at(t_pattern pattern, t_tuple point)
{
	int floored_distance = (int)floor(hypot(point.x, point.z));
	if (floored_distance % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_pattern		set_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix();
	return (pattern);
}

t_tuple		checker_at(t_pattern pattern, t_tuple point)
{
	int floored_sum = (int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z);
	if (floored_sum % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_tuple pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple pattern_point;

	object_point = multiply_matrix_by_tuple(inverse_matrix(shape.transform), world_point);
	pattern_point = multiply_matrix_by_tuple(inverse_matrix(pattern.transform), object_point);

	if (shape.material.has_pattern == PATTERN_STRIPE)
		return (stripe_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_GRADIENT)
		return (gradient_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_RING)
		return (ring_at(pattern, pattern_point));
	else
		return (checker_at(pattern, pattern_point));
}


t_tuple	lighting(t_material material, t_shape shape, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv, int in_shadow)
{
	t_tuple color;
	t_tuple effective_color;
	t_tuple lightv;
	t_tuple reflectv;
	t_tuple ambient;
	double reflect_dot_eye;
	double light_dot_normal;
	t_tuple diffuse;
	t_tuple specular;
	double factor;

	if (material.has_pattern)
		color = pattern_at_object(material.pattern, shape, position);
	else
		color = material.color;
	effective_color = multiply_color(color, light.intensity);
	lightv = normalize(substract_tuple(light.position, position));
	ambient = multiply_tuple_scalar(effective_color, material.ambient);
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

void insertion_sort_intersections(t_intersection *array, int count)
{
	t_intersection key;
	int i;
	int j;
	
	i = 1;
	while (i < count)
	{
		key = array[i];
		j = i - 1;
		if (array[j].t <= key.t)
		{
			i++;
			continue;
		}
		while (j >= 0 && array[j].t > key.t)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
		i++;
	}
}

// Function to find the intersections in the world
t_intersects intersect_scene(t_scene *world, t_ray ray)
{
	t_intersects xs;
	t_intersection *temp_array;
	t_intersection *xs_array;
	t_intersects temp;
	int total_intersections = 0;
	int i;
	int index;
	temp_array = NULL;

	// Allocate memory for intersections dynamically (in case there are more than 2 intersections)
	xs_array = NULL;

	// First pass: Count total intersections
	i = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		total_intersections += temp.count;
		free_intersects(&temp);
		i++;
	}
	//printf("Total intersections: %d\n", total_intersections);
	// Allocate memory once
	if (total_intersections > 0)
	{
		xs_array = malloc(sizeof(t_intersection) * total_intersections);
		if (!xs_array)
		{
			xs.count = 0;
			xs.array = NULL;
			return xs;
		}
	}

	// Second pass: Store all intersections
	index = 0;
	i = 0;
	while (i < world->shape_count)
	{
		temp = intersect(&world->shapes[i], ray);
		if (temp.count > 0)
		{
			ft_memcpy(xs_array + index, temp.array, sizeof(t_intersection) * temp.count);
			index += temp.count;
		}
		free_intersects(&temp);
		i++;
	}

	insertion_sort_intersections(xs_array, total_intersections);
	xs.count = total_intersections;
	xs.array = xs_array;
	return (xs);
}


t_tuple reflected_color(t_scene *world, t_intersection comps, int remaining)
{
	t_tuple	color;
	t_tuple	reflect_color;

	if (remaining <= 0)
		return (create_color(0, 0, 0));
	if (comps.object->material.reflective <= EPSILON)
		return (create_color(0, 0, 0));
	color = color_at(world, create_ray(comps.over_point, comps.reflectv), remaining - 1);
	reflect_color = multiply_tuple_scalar(color, comps.object->material.reflective);
	return (reflect_color);
}

t_tuple refracted_color(t_scene *world, t_intersection comps, int remaining)
{
	t_tuple	refract_color;
	t_ray	refracted_ray;
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	double	cos_t;
	t_tuple	direction;

	if (remaining <= 0 || comps.object->material.transparency < EPSILON)
		return (create_color(0, 0, 0));
	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.eyev, comps.normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (create_color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	direction = substract_tuple(multiply_tuple_scalar(comps.normalv, n_ratio * cos_i - cos_t), multiply_tuple_scalar(comps.eyev, n_ratio));
	if (comps.inside)
		refracted_ray = create_ray(comps.under_point, direction);
	else
		refracted_ray = create_ray(comps.over_point, direction);
	refract_color = color_at(world, refracted_ray, remaining - 1);
	return (multiply_tuple_scalar(refract_color, comps.object->material.transparency));
}
 /* 
 The function uses Schlick's approximation to compute the reflectance.
 Schlick's approximation is a simple function that estimates the reflectance at an intersection.
 It is based on the Fresnel equations, which describe the behavior of light when it moves between two media.
 The Fresnel equations are complex, but Schlick's approximation provides a simple way to estimate the reflectance.
 The function takes the intersection as a parameter and returns the reflectance at that intersection.
 The reflectance is a value between 0 and 1, where 0 means no reflection and 1 means full reflection.
 */
double schlick(t_intersection comps)
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


/* The function ought to return the color at the intersection encapsulated by comps, in the given world.
** P.S. If we have more than one light source, we will have to loop through all of them and sum the results.
** @param world: t_scene The world.
** @param comps: t_intersection The intersection.
** @return: t_tuple The color at the intersection.
*/
t_tuple	shade_hit(t_scene *world, t_intersection comps, int remaining, t_intersects *xs)
{
	int	shadowed;
	t_tuple	surface;
	t_tuple reflected;
	t_tuple refracted;
	double	reflectance;
	t_tuple	color;

	shadowed = is_shadowed(*world, comps.over_point);
	surface = lighting(comps.object->material, *comps.object, world->light, comps.over_point, comps.eyev, comps.normalv, shadowed);
	reflected = reflected_color(world, comps, remaining);
	refracted = refracted_color(world, comps, remaining);
	// If the material is both reflective and transparent, use Schlick's approximation.
	if (comps.object->material.transparency > EPSILON && comps.object->material.reflective > EPSILON)
	{
		reflectance = schlick(comps);  // Compute the reflectance at the intersection.
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
		return create_color(0, 0, 0);
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


int is_shadowed(t_scene world, t_tuple point)
{
	t_tuple	v;
	double	distance;
	t_ray	r;
	t_intersects	xs;
	t_intersection	*hit_obj;

	v = substract_tuple(world.light.position, point);
	r = create_ray(point, normalize(v));
	xs = intersect_scene(&world, r);
	if (xs.count == 0)
	{
		free(xs.array);
		return 0;
	}
	hit_obj = hit(xs);
	distance = magnitude(v);
	if (hit_obj && hit_obj->t < distance)
	{
		free(xs.array);//free_intersects(&xs);
		return (1);
	}
	free(xs.array);//free_intersects(&xs);
	return (0);
}
