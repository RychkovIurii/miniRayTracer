/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:50:41 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 14:08:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Computes the normal vector at a given point on the surface of a cylinder.
** This function determines whether the point lies on the cylinder's curved
** surface or its caps and returns the appropriate normal.
** @param cylinder: The cylinder shape being tested.
** @param point: The point on the cylinder where the normal is calculated.
** @returns A t_tuple representing the normal vector at the given point.
*/
static t_tuple	local_normal_at_cylinder(t_shape cylinder, t_tuple point)
{
	double	distance;

	distance = point.x * point.x + point.z * point.z;
	if (distance < (cylinder.radius * cylinder.radius)
		&& point.y >= cylinder.max - EPSILON)
		return (vector(0, 1, 0));
	else if (distance < (cylinder.radius * cylinder.radius)
		&& point.y <= cylinder.min + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
}

/* 
** Computes the normal vector at a given point on the surface of a cone.
** This function determines whether the point lies on the cone's slanted surface
** or its caps and returns the appropriate normal.
** @param cone: The cone shape being tested.
** @param point: The point on the cone's surface where the normal is calculated.
** @returns A t_tuple representing the normal vector at the given point.
*/
static t_tuple	local_normal_at_cone(t_shape cone, t_tuple point)
{
	double	distance;
	double	y_factor;
	t_tuple	normal;

	distance = (point.x * point.x + point.z * point.z);
	if (cone.closed && fabs(point.y - cone.min) < EPSILON
		&& distance <= cone.radius * cone.radius)
		return (vector(0, -1, 0));
	if (cone.closed && fabs(point.y - cone.max) < EPSILON
		&& distance <= cone.radius * cone.radius)
		return (vector(0, 1, 0));
	y_factor = sqrt(distance) * (cone.radius / cone.height);
	y_factor *= cone.radius / cone.height;
	normal = vector(point.x, y_factor, point.z);
	if (dot(normal, point) < 0)
		normal = negate_tuple(normal);
	return (normal);
}

/*
** Computes the normal vector at a given point on the surface of a shape.
** This function determines the shape type and calls the appropriate
** local_normal_at function.
** @param shape: The shape being tested.
** @param world_point: The point on the surface where the normal is calculated.
** @returns A t_tuple representing the normal vector at the given point.
*/
t_tuple	normal_at(t_shape *shape, t_tuple world_point)
{
	t_tuple	surface_normal;
	t_tuple	world_normal;
	t_tuple	local_point;
	t_tuple	local_normal;

	local_point = multiply_matrix_by_tuple(shape->transform_inv, world_point);
	if (shape->type == SHAPE_SPHERE)
		local_normal = substract_tuple(local_point, shape->center);
	else if (shape->type == SHAPE_CYLINDER)
		local_normal = local_normal_at_cylinder(*shape, local_point);
	else if (shape->type == SHAPE_CONE)
		local_normal = local_normal_at_cone(*shape, local_point);
	else
		local_normal = vector(0, 1, 0);
	world_normal = multiply_matrix_by_tuple(shape->transpose_inv, local_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}
