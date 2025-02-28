/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:45:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 14:00:38 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Create a new matrix.
** The matrix is a 4x4 array of doubles.
** The matrix does not allocate memory.
** @returns a new identity matrix.
*/
t_matrix	identity_matrix(void)
{
	t_matrix	id;

	ft_bzero(&id, sizeof(t_matrix));
	id.matrix[0][0] = 1.0;
	id.matrix[1][1] = 1.0;
	id.matrix[2][2] = 1.0;
	id.matrix[3][3] = 1.0;
	return (id);
}

/* Multiply two matrices.
** @param a: The first matrix.
** @param b: The second matrix.
** @returns a new matrix that is the result of the multiplication.
*/
t_matrix	multiply_matrices(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	ft_bzero(&result, sizeof(t_matrix));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

/* Multiply a matrix by a tuple.
** @param a: The matrix.
** @param b: The tuple.
** @returns a new tuple that is the result of the multiplication.
*/
t_tuple	multiply_matrix_by_tuple(t_matrix a, t_tuple b)
{
	t_tuple	result;

	result.x = a.matrix[0][0] * b.x + a.matrix[0][1] * b.y
		+ a.matrix[0][2] * b.z + a.matrix[0][3] * b.w;
	result.y = a.matrix[1][0] * b.x + a.matrix[1][1] * b.y
		+ a.matrix[1][2] * b.z + a.matrix[1][3] * b.w;
	result.z = a.matrix[2][0] * b.x + a.matrix[2][1] * b.y
		+ a.matrix[2][2] * b.z + a.matrix[2][3] * b.w;
	result.w = a.matrix[3][0] * b.x + a.matrix[3][1] * b.y
		+ a.matrix[3][2] * b.z + a.matrix[3][3] * b.w;
	return (result);
}

/* Transpose a matrix.
** @param a: The matrix.
** @returns a new matrix that is the transpose of the given matrix.
*/
t_matrix	transpose_matrix(t_matrix a)
{
	t_matrix	result;
	int			i;
	int			j;

	ft_bzero(&result, sizeof(t_matrix));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.matrix[j][i] = a.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

/* Calculate the inverse of a matrix.
** @param a: The matrix.
** @returns the inverse of the matrix.
*/
t_matrix	inverse_matrix(t_matrix a)
{
	t_matrix	inverse;
	double		det;
	int			i;
	int			j;

	det = determinant(a);
	if (fabs(det) < EPSILON)
		return (identity_matrix());
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			inverse.matrix[j][i] = cofactor_matrix(a, i, j) / det;
			j++;
		}
		i++;
	}
	return (inverse);
}
