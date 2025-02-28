/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:38:18 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 14:46:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Function to add two tuples.
** @param a: The first tuple.
** @param b: The second tuple.
** @return The new tuple.
*/
t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x + b.x;
	tuple.y = a.y + b.y;
	tuple.z = a.z + b.z;
	tuple.w = a.w + b.w;
	return (tuple);
}

/*
** Function to subtract two tuples.
** @param a: The first tuple.
** @param b: The second tuple.
** @return The new tuple.
*/
t_tuple	substract_tuple(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x - b.x;
	tuple.y = a.y - b.y;
	tuple.z = a.z - b.z;
	tuple.w = a.w - b.w;
	return (tuple);
}

/*
** Function to negate a tuple.
** @param a: The tuple to negate.
** @return The new tuple.
*/
t_tuple	negate_tuple(t_tuple a)
{
	t_tuple	tuple;

	tuple.x = -a.x;
	tuple.y = -a.y;
	tuple.z = -a.z;
	tuple.w = -a.w;
	return (tuple);
}

/*
** Function to multiply scalar by a tuple.
** @param a: The tuple.
** @param scalar: double The scalar.
** @return The new tuple.
*/
t_tuple	multiply_tuple_scalar(t_tuple a, double scalar)
{
	t_tuple	tuple;

	tuple.x = a.x * scalar;
	tuple.y = a.y * scalar;
	tuple.z = a.z * scalar;
	tuple.w = a.w * scalar;
	return (tuple);
}

/*
** Function to compare two tuples.
** @param a: The first tuple.
** @param b: The second tuple.
** @return 1 if the tuples are equal, 0 otherwise.
*/
int	is_tuples_equal(t_tuple a, t_tuple b)
{
	if (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON
		&& fabs(a.z - b.z) < EPSILON && fabs(a.w - b.w) < EPSILON)
		return (1);
	return (0);
}
