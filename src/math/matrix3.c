/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:36:40 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 16:56:43 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Submatrix returns a copy of the given matrix with the row and column removed.
** @param a: The matrix.
** @param row: The row to remove.
** @param column: The column to remove.
** @returns a new 3x3 matrix.
*/
static t_matrix3x3	submatrix(t_matrix a, int row, int column)
{
	t_matrix3x3	sub;
	int			i;
	int			j;
	int			x;
	int			y;

	x = 0;
	i = 0;
	while (i < 4)
	{
		if (i != row)
		{
			j = 0;
			y = 0;
			while (j < 4)
			{
				if (j != column)
					sub.matrix[x][y++] = a.matrix[i][j];
				j++;
			}
			x++;
		}
		i++;
	}
	return (sub);
}

/* Calculate the determinant of a 3x3 matrix.
** @param m: The 3x3 matrix.
** @returns the determinant of the matrix.
*/
static double	determinant3x3(t_matrix3x3 m)
{
	double	det;

	det = m.matrix[0][0] * (m.matrix[1][1] * m.matrix[2][2]
			- m.matrix[1][2] * m.matrix[2][1]) - m.matrix[0][1]
		* (m.matrix[1][0] * m.matrix[2][2] - m.matrix[1][2] * m.matrix[2][0])
		+ m.matrix[0][2]
		* (m.matrix[1][0] * m.matrix[2][1] - m.matrix[1][1] * m.matrix[2][0]);
	return (det);
}

/* Calculate the minor of a 3x3 matrix.
** @param a: The matrix 4x4.
** @param row: The row to remove.
** @param column: The column to remove.
** @returns the minor of the matrix.
*/
static double	minor_matrix(t_matrix a, int row, int column)
{
	t_matrix3x3	sub;

	sub = submatrix(a, row, column);
	return (determinant3x3(sub));
}

/* Calculate the cofactor of a 3x3 matrix.
** @param a: The matrix 4x4.
** @param row: The row to remove.
** @param column: The column to remove.
** @returns the cofactor of the matrix.
*/
double	cofactor_matrix(t_matrix a, int row, int column)
{
	double	minor;
	double	cofactor;

	minor = minor_matrix(a, row, column);
	if ((row + column) % 2 == 0)
		cofactor = minor;
	else
		cofactor = -minor;
	return (cofactor);
}

/* Calculate the determinant of a 4x4 matrix.
** @param a: The matrix.
** @returns the determinant of the matrix.
*/
double	determinant(t_matrix a)
{
	double	det;

	det = a.matrix[0][0] * cofactor_matrix(a, 0, 0)
		+ a.matrix[0][1] * cofactor_matrix(a, 0, 1)
		+ a.matrix[0][2] * cofactor_matrix(a, 0, 2)
		+ a.matrix[0][3] * cofactor_matrix(a, 0, 3);
	return (det);
}
