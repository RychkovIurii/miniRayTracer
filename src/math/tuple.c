/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:38:19 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 14:42:59 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Function to create a color tuple.
@param r, g, b: color values.
@returns a tuple that represents a color. */
t_tuple	create_color(double r, double g, double b)
{
	t_tuple	tuple;

	tuple.x = r;
	tuple.y = g;
	tuple.z = b;
	tuple.w = 0.0;
	return (tuple);
}

/* Hadamard product is a term for element-wise multiplication of two tuples.
We can call it a "multiply_color" as well.
@param a, b: tuples to multiply.
@returns a new tuple that is the element-wise multiplication of the tuples.
*/
t_tuple	multiply_color(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x * b.x;
	tuple.y = a.y * b.y;
	tuple.z = a.z * b.z;
	tuple.w = 0.0;
	return (tuple);
}

/*
** Function to create a point.
** @param x: The x coordinate of the point.
** @param y: The y coordinate of the point.
** @param z: The z coordinate of the point.
** @return The tuple of the point.
*/
t_tuple	point(double x, double y, double z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 1.0;
	return (tuple);
}

/*
** Function to create a vector.
** @param x: The x coordinate of the vector.
** @param y: The y coordinate of the vector.
** @param z: The z coordinate of the vector.
** @return The tuple of the vector.
*/
t_tuple	vector(double x, double y, double z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 0.0;
	return (tuple);
}
