/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:45:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/17 13:01:34 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix create_matrix(int size)
{
	t_matrix matrix;
	int i, j;

	matrix.size = size;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			matrix.matrix[i][j] = 0.0;
		}
	}
	return matrix;
}

t_matrix identity_matrix(int size)
{
	t_matrix id = create_matrix(size);
	for (int i = 0; i < size; i++)
		id.matrix[i][i] = 1;
	return id;
}

/* Check if two matrices are equal. */
int	is_matrices_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	if (a.size != b.size)
		return (0);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			/* if (a.matrix[i][j] != b.matrix[i][j]) */
			if (fabs(a.matrix[i][j] - b.matrix[i][j]) > 1e-5) // 1e-5 is comparison within a small tolerance
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

	result = create_matrix(a.size);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			k = 0;
			while (k < a.size)
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

	result = create_matrix(a.size); //shall we create a new matrix here?
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
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

	result = create_matrix(4);
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

	if (x == 0 || y == 0 || z == 0)
    {
        printf("Error: Scaling matrix has a zero component and is not invertible!\n");
        exit(1);
    }
	result = identity_matrix(4);
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

	result = create_matrix(4);
	result.matrix[0][0] = 1;
	result.matrix[1][1] = cos(radian);
	result.matrix[1][2] = -sin(radian);
	result.matrix[2][1] = sin(radian);
	result.matrix[2][2] = cos(radian);
	result.matrix[3][3] = 1;
	return (result);
}

t_matrix	rotation_y_matrix(double radian)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = cos(radian);
	result.matrix[0][2] = sin(radian);
	result.matrix[1][1] = 1;
	result.matrix[2][0] = -sin(radian);
	result.matrix[2][2] = cos(radian);
	result.matrix[3][3] = 1;
	return (result);
}

t_matrix	rotation_z_matrix(double radian)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = cos(radian);
	result.matrix[0][1] = -sin(radian);
	result.matrix[1][0] = sin(radian);
	result.matrix[1][1] = cos(radian);
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	return (result);
}

/* Shearing matrix. */
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = 1;
	result.matrix[0][1] = xy;
	result.matrix[0][2] = xz;
	result.matrix[1][0] = yx;
	result.matrix[1][1] = 1;
	result.matrix[1][2] = yz;
	result.matrix[2][0] = zx;
	result.matrix[2][1] = zy;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	return (result);
}

/* Submatrix returns a copy of the given matrix with the given row and column removed. */
t_matrix	submatrix(t_matrix a, int row, int column)
{
	t_matrix	sub;
	int		i;
	int		j;
	int		x;
	int		y;

	if (a.size < 2)
	{
		printf("Error: Matrix is too small\n"); // Handle error: matrix is too small
		return (a);
	}
	sub = create_matrix(a.size - 1);
	x = 0;
	i = 0;
	while (i < a.size)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		y = 0;
		while (j < a.size)
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

/* Calculate the minor of matrix. */
double	minor_matrix(t_matrix a, int row, int column)
{
	t_matrix	sub;
	double	det;

	sub = submatrix(a, row, column);
	det = determinant(sub);
	//free_matrix(sub);
	return (det);
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
	int		i;

	i = 0;
	det = 0;
	if (a.size == 2)
		return (a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0]);
	while (i < a.size)
	{
		det += a.matrix[0][i] * cofactor_matrix(a, 0, i);
		i++;
	}
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

	/* if (a.matrix == NULL)
	{
		printf("Error: Received NULL matrix\n");
		exit(1); // Handle error, potentially return an invalid matrix
	} */
	det = determinant(a);
	if (fabs(det) < 1e-6) //(det == 0)
	{
		printf("Matrix is not invertible\n");
		//print_matrix(a);
		return (identity_matrix(4));
	}
	inverse = create_matrix(a.size);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			inverse.matrix[j][i] = cofactor_matrix(a, i, j) / det;
			j++;
		}
		i++;
	}
	return (inverse);
}
