/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:01:33 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/04 20:47:01 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	assign_default_material(t_material *material)
{
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 300.0;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
	material->has_pattern = 0;
}

void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_SPHERE;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].radius = diameter / 2;
	assign_default_material(&rt->scene->shapes[i].material);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shapes[i].material.ambient = rt->scene->ambient.ratio;
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shapes[i].scale = vector(1, 1, 1);
	rt->scene->shape_count++;
}

void	add_plane(t_rt *rt, t_file data)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_PLANE;
	rt->scene->shapes[i].center = string_to_point(data.coordinates);
	rt->scene->shapes[i].normal = string_to_vector(data.normal);
	assign_default_material(&rt->scene->shapes[i].material);
	rt->scene->shapes[i].material.color = string_to_color(data.colors);
	rt->scene->shapes[i].material.ambient = rt->scene->ambient.ratio;
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shapes[i].scale = vector(1, 1, 1);
	rt->scene->shape_count++;
}

void	add_cylinder(t_rt *rt, t_file data)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_CYLINDER;
	rt->scene->shapes[i].closed = 1;
	rt->scene->shapes[i].center = string_to_point(data.coordinates);
	rt->scene->shapes[i].normal = string_to_vector(data.normal);
	assign_default_material(&rt->scene->shapes[i].material);
	rt->scene->shapes[i].material.color = string_to_color(data.colors);
	rt->scene->shapes[i].material.ambient = rt->scene->ambient.ratio;
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shapes[i].scale = vector(1, 1, 1);
	rt->scene->shape_count++;
}
