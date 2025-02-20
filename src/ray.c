/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:36:08 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/17 13:48:58 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray			create_ray(t_tuple origin, t_tuple direction)
{
	t_ray		result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_tuple			get_ray_position(t_ray ray, double t)
{
	t_tuple		result;

	result = add_tuple(ray.origin, multiply_tuple_scalar(ray.direction, t));
	return (result);
}

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray		result;

	result.origin = multiply_matrix_by_tuple(matrix, ray.origin);
	result.direction = multiply_matrix_by_tuple(matrix, ray.direction);
	return (result);
}
