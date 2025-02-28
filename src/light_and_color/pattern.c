/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:51:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 14:59:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Function to return the color of the stripe pattern at a given point.
** @param pattern: The pattern.
** @param point: The point.
** @return The color at the point.
*/
t_tuple	stripe_at(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

/*
** Function to return the color of the gradient pattern at a given point.
** @param pattern: The pattern.
** @param point: The point.
** @return The color at the point.
*/
t_tuple	gradient_at(t_pattern pattern, t_tuple point)
{
	t_tuple	distance;
	double	fraction;

	distance = substract_tuple(pattern.color_b, pattern.color_a);
	fraction = point.x - floor(point.x);
	return (
		add_tuple(pattern.color_a, multiply_tuple_scalar(distance, fraction)));
}

/*
** Function to return the color of the ring pattern at a given point.
** @param pattern: The pattern.
** @param point: The point.
** @return The color at the point.
*/
t_tuple	ring_at(t_pattern pattern, t_tuple point)
{
	int	floored_distance;

	floored_distance = (int)floor(hypot(point.x, point.z));
	if (floored_distance % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

/*
** Function to return the color of the checker pattern at a given point.
** @param pattern: The pattern.
** @param point: The point.
** @return The color at the point.
*/
t_tuple	checker_at(t_pattern pattern, t_tuple point)
{
	int	floored_sum;

	floored_sum = (int)floor(point.x) + (int)floor(point.y)
		+ (int)floor(point.z);
	if (floored_sum % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

/*
** Function to return the color of the pattern at a given point on an object.
** @param pattern: The pattern.
** @param shape: The shape.
** @param world_point: The point.
** @return The color at the point.
*/
t_tuple	pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = multiply_matrix_by_tuple(shape.transform_inv, world_point);
	pattern_point = multiply_matrix_by_tuple(
			inverse_matrix(pattern.transform), object_point);
	if (shape.material.has_pattern == PATTERN_STRIPE)
		return (stripe_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_GRADIENT)
		return (gradient_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_RING)
		return (ring_at(pattern, pattern_point));
	else
		return (checker_at(pattern, pattern_point));
}
