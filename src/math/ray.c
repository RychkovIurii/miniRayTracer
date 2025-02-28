/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:36:08 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 17:33:05 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Create a ray with given origin and direction
** @param origin: the origin of the ray
** @param direction: the direction of the ray
** @returns the created ray
*/
t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

/*
** Get the position of a point on a ray
** @param ray: the ray
** @param t: the distance from the origin of the ray
** @returns the position of the point
*/
t_tuple	get_ray_position(t_ray ray, double t)
{
	t_tuple	result;

	result = add_tuple(ray.origin, multiply_tuple_scalar(ray.direction, t));
	return (result);
}

/*
** Transform a ray by a matrix
** @param ray: the ray to transform
** @param matrix: the matrix to transform the ray by
** @returns the transformed ray
*/
t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	result;

	result.origin = multiply_matrix_by_tuple(matrix, ray.origin);
	result.direction = multiply_matrix_by_tuple(matrix, ray.direction);
	return (result);
}
