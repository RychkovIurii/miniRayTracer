/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:01:33 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/20 22:35:47 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_SPHERE;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].radius = diameter / 2;
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shapes[i].material.ambient = rt->scene->ambient.ratio;
	rt->scene->shapes[i].material.diffuse = 0.3;
	rt->scene->shapes[i].material.specular = 1.0;
	rt->scene->shapes[i].material.shininess = 300.0;
	/* rt->scene->shapes[i].material.reflective = 0.9;
	rt->scene->shapes[i].material.transparency = 0.0;
	rt->scene->shapes[i].material.refractive_index = 1.0; */
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shape_count++;
}

void	add_plane(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_PLANE;
	rt->scene->shapes[i].point_on_plane = string_to_point(coordinates);
	rt->scene->shapes[i].normal = string_to_vector(normal);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shapes[i].material.diffuse = 0.8;
	rt->scene->shapes[i].material.specular = 0.4;
	rt->scene->shapes[i].material.shininess = 150.0;
	/* rt->scene->shapes[i].material.reflective = 0.2;
	rt->scene->shapes[i].material.transparency = 0.0;
	rt->scene->shapes[i].material.refractive_index = 0.0; */
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shape_count++;
}

void	add_cylinder(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = SHAPE_CYLINDER;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].normal = string_to_vector(normal);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shapes[i].material.diffuse = 0.8;
	rt->scene->shapes[i].material.specular = 0.4;
	rt->scene->shapes[i].material.shininess = 150.0;
	rt->scene->shapes[i].transform = identity_matrix();
	rt->scene->shape_count++;
}
