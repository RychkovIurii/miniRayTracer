/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:27:20 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 16:21:04 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	*add_sphere_bonus(t_rt *rt, char **coord, char **colors, double dia)
{
	int		i;
	t_shape	*sphere;

	i = rt->scene->shape_count;
	sphere = &rt->scene->shapes[i];
	sphere->type = SHAPE_SPHERE;
	sphere->center = string_to_point(coord);
	sphere->radius = dia / 2;
	sphere->material.color = string_to_color(colors);
	sphere->material.ambient = rt->scene->ambient.ratio;
	sphere->transform = identity_matrix();
	sphere->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (sphere);
}

t_shape	*add_plane_bonus(t_rt *rt, t_file data)
{
	int		i;
	t_shape	*plane;

	i = rt->scene->shape_count;
	plane = &rt->scene->shapes[i];
	plane->type = SHAPE_PLANE;
	plane->center = string_to_point(data.coordinates);
	plane->normal = string_to_vector(data.normal);
	plane->material.color = string_to_color(data.colors);
	plane->material.ambient = rt->scene->ambient.ratio;
	plane->transform = identity_matrix();
	plane->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (plane);
}

t_shape	*add_cylinder_bonus(t_rt *rt, t_file data)
{
	int		i;
	t_shape	*cylinder;

	i = rt->scene->shape_count;
	cylinder = &rt->scene->shapes[i];
	cylinder->type = SHAPE_CYLINDER;
	cylinder->closed = 1;
	cylinder->center = string_to_point(data.coordinates);
	cylinder->normal = string_to_vector(data.normal);
	cylinder->material.color = string_to_color(data.colors);
	cylinder->material.ambient = rt->scene->ambient.ratio;
	cylinder->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (cylinder);
}

t_shape	*add_cone_bonus(t_rt *rt, t_file data)
{
	int		i;
	t_shape	*cone;

	i = rt->scene->shape_count;
	cone = &rt->scene->shapes[i];
	cone->type = SHAPE_CONE;
	cone->closed = 1;
	cone->center = string_to_point(data.coordinates);
	cone->normal = string_to_vector(data.normal);
	cone->material.color = string_to_color(data.colors);
	cone->material.ambient = rt->scene->ambient.ratio;
	cone->transform = identity_matrix();
	cone->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (cone);
}
