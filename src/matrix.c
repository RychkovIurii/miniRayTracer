/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:45:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/19 20:45:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix identity_matrix(void)
{
	t_matrix id;

	ft_bzero(&id, sizeof(t_matrix));
	id.matrix[0][0] = 1.0;
	id.matrix[1][1] = 1.0;
	id.matrix[2][2] = 1.0;
	id.matrix[3][3] = 1.0;
	return (id);
}

/* Check if two matrices are equal. */
int	is_matrices_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (fabs(a.matrix[i][j] - b.matrix[i][j]) > EPSILON)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* Multiply two matrices. */
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

/* Multiply a matrix by a tuple. */
t_tuple	multiply_matrix_by_tuple(t_matrix a, t_tuple b)
{
	t_tuple	result;

	result.x = a.matrix[0][0] * b.x + a.matrix[0][1] * b.y + a.matrix[0][2] * b.z + a.matrix[0][3] * b.w;
	result.y = a.matrix[1][0] * b.x + a.matrix[1][1] * b.y + a.matrix[1][2] * b.z + a.matrix[1][3] * b.w;
	result.z = a.matrix[2][0] * b.x + a.matrix[2][1] * b.y + a.matrix[2][2] * b.z + a.matrix[2][3] * b.w;
	result.w = a.matrix[3][0] * b.x + a.matrix[3][1] * b.y + a.matrix[3][2] * b.z + a.matrix[3][3] * b.w;

	return (result);
}

/* Transpose a matrix. */
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

/* Translation matrix. */
t_matrix	translation_matrix(double x, double y, double z)
{
	t_matrix	result;

	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = 1;
	result.matrix[1][1] = 1;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	result.matrix[0][3] = x;
	result.matrix[1][3] = y;
	result.matrix[2][3] = z;
	return (result);
}

/* Scaling matrix. */
t_matrix	scaling_matrix(double x, double y, double z)
{
	t_matrix	result;

	if (fabs(x) < EPSILON || fabs(y) < EPSILON || fabs(z) < EPSILON)
		return (identity_matrix()); 
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = x;
	result.matrix[1][1] = y;
	result.matrix[2][2] = z;
	result.matrix[3][3] = 1;
	return (result);
}

/* Rotation matrix. */

t_matrix	rotation_x_matrix(double radian)
{
	t_matrix	result;
	double cos_r;
	double sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = 1.0;
	result.matrix[1][1] = cos_r;
	result.matrix[1][2] = -sin_r;
	result.matrix[2][1] = -sin_r;
	result.matrix[2][2] = cos_r;
	result.matrix[3][3] = 1.0;
	return (result);
}

t_matrix	rotation_y_matrix(double radian)
{
	t_matrix	result;
	double cos_r;
	double sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = cos_r;
	result.matrix[0][2] = sin_r;
	result.matrix[1][1] = 1.0;
	result.matrix[2][0] = -sin_r;
	result.matrix[2][2] = cos_r;
	result.matrix[3][3] = 1.0;
	return (result);
}

t_matrix	rotation_z_matrix(double radian)
{
	t_matrix	result;
	double cos_r;
	double sin_r;

	cos_r = cos(radian);
	sin_r = sin(radian);
	ft_bzero(&result, sizeof(t_matrix));
	result.matrix[0][0] = cos_r;
	result.matrix[0][1] = -sin_r;
	result.matrix[1][0] = sin_r;
	result.matrix[1][1] = cos_r;
	result.matrix[2][2] = 1.0;
	result.matrix[3][3] = 1.0;
	return (result);
}

/* Shearing matrix. */
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_matrix	result;

	result = identity_matrix();
	result.matrix[0][1] = xy;
	result.matrix[0][2] = xz;
	result.matrix[1][0] = yx;
	result.matrix[1][2] = yz;
	result.matrix[2][0] = zx;
	result.matrix[2][1] = zy;
	return (result);
}

/* Submatrix returns a copy of the given matrix with the given row and column removed. */
t_matrix3x3	submatrix(t_matrix a, int row, int column)
{
	t_matrix3x3	sub;
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	while (i < 4)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		y = 0;
		while (j < 4)
		{
			if (j == column)
			{
				j++;
				continue;
			}
			sub.matrix[x][y] = a.matrix[i][j];
			y++;
			j++;
		}
		x++;
		i++;
	}
	return (sub);
}

double determinant3x3(t_matrix3x3 m)
{
	double	det;

	det = m.matrix[0][0] * (m.matrix[1][1] * m.matrix[2][2] - m.matrix[1][2] * m.matrix[2][1]) -
	m.matrix[0][1] * (m.matrix[1][0] * m.matrix[2][2] - m.matrix[1][2] * m.matrix[2][0]) +
	m.matrix[0][2] * (m.matrix[1][0] * m.matrix[2][1] - m.matrix[1][1] * m.matrix[2][0]);
	return (det);
}

/* Calculate the minor of matrix. */
double	minor_matrix(t_matrix a, int row, int column)
{
	t_matrix3x3	sub;

	sub = submatrix(a, row, column);
	return (determinant3x3(sub));
}


/* Calculate the cofactor of a 3x3 matrix. */
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

/* Calculate the determinant of a matrix. */
double	determinant(t_matrix a)
{
	double	det;

	det = a.matrix[0][0] * cofactor_matrix(a, 0, 0) +
	a.matrix[0][1] * cofactor_matrix(a, 0, 1) +
	a.matrix[0][2] * cofactor_matrix(a, 0, 2) +
	a.matrix[0][3] * cofactor_matrix(a, 0, 3);
	return (det);
}

/* Is matrix invertible */
int		is_invertible(t_matrix a)
{
	if (determinant(a) == 0)
		return (0);
	return (1);
}

/* Inverse matrix. */
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
