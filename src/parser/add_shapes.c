/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:01:33 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/20 12:51:09 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 1;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].radius = diameter / 2;
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shape_count++;
}

void	add_plane(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 2;
	rt->scene->shapes[i].point_on_plane = string_to_point(coordinates);
	rt->scene->shapes[i].normal = string_to_vector(normal);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shape_count++;
}

void	add_cylinder(t_rt *rt, char **coordinates, char **normal, char **colors)
{
	int	i;

	i = rt->scene->shape_count;
	rt->scene->shapes[i].type = 3;
	rt->scene->shapes[i].center = string_to_point(coordinates);
	rt->scene->shapes[i].normal = string_to_vector(normal);
	rt->scene->shapes[i].material.color = string_to_color(colors);
	rt->scene->shape_count++;
}
