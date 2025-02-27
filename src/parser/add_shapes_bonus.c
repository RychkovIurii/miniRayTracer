/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:27:20 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 17:21:05 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	*add_sphere(t_rt *rt, char **coord, char **colors, double diameter)
{
	int		i;
	t_shape	*sphere;

	i = rt->scene->shape_count;
	sphere = &rt->scene->shapes[i];
	sphere->type = SHAPE_SPHERE;
	sphere->center = string_to_point(coord);
	sphere->radius = diameter / 2;
	sphere->material.color = string_to_color(colors);
	sphere->material.ambient = rt->scene->ambient.ratio;
	sphere->transform = identity_matrix();
	sphere->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (sphere);
}

t_shape	*add_plane(t_rt *rt, char **coord, char **normal, char **colors)
{
	int		i;
	t_shape	*plane;

	i = rt->scene->shape_count;
	plane = &rt->scene->shapes[i];
	plane->type = SHAPE_PLANE;
	plane->center = string_to_point(coord);
	plane->normal = string_to_vector(normal);
	plane->material.color = string_to_color(colors);
	plane->material.ambient = rt->scene->ambient.ratio;
	plane->transform = identity_matrix();
	plane->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (plane);
}

t_shape	*add_cylinder(t_rt *rt, char **coord, char **normal, char **colors)
{
	int		i;
	t_shape	*cylinder;

	i = rt->scene->shape_count;
	cylinder = &rt->scene->shapes[i];
	cylinder->type = SHAPE_CYLINDER;
	cylinder->closed = 1;
	cylinder->center = string_to_point(coord);
	cylinder->normal = string_to_vector(normal);
	cylinder->material.color = string_to_color(colors);
	cylinder->material.ambient = rt->scene->ambient.ratio;
	cylinder->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (cylinder);
}

t_shape	*add_cone(t_rt *rt, char **coord, char **normal, char **colors)
{
	int		i;
	t_shape	*cone;

	i = rt->scene->shape_count;
	cone = &rt->scene->shapes[i];
	cone->type = SHAPE_CONE;
	cone->closed = 1;
	cone->center = string_to_point(coord);
	//rt->scene->shapes[i].center.y += rt->scene->shapes[i].height / 2;  //forced center.y to be higher by cone height
	cone->normal = string_to_vector(normal);
	cone->material.color = string_to_color(colors);
	cone->material.ambient = rt->scene->ambient.ratio;
	cone->transform = identity_matrix();
	cone->scale = vector(1, 1, 1);
	rt->scene->shape_count++;
	return (cone);
}
