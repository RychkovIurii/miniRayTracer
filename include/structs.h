/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 17:16:40 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef struct	s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_matrix3x3
{
	double matrix[3][3];
} t_matrix3x3;

typedef struct	s_matrix
{
	double	matrix[4][4];
}			t_matrix;

typedef struct	s_ray
{
	t_tuple	origin;		//point
	t_tuple	direction;	//vector
}			t_ray;

typedef struct	s_pattern
{
	t_tuple		color_a;
	t_tuple		color_b;
	t_matrix	transform;
}				t_pattern;

typedef struct	s_material
{
	t_tuple		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	t_pattern	pattern;
	int			has_pattern;
}			t_material;

typedef enum { SHAPE_SPHERE, SHAPE_PLANE } t_shape_type;

typedef struct s_shape {
	t_matrix		transform;
	t_tuple			center;
	t_tuple			scale;
	t_tuple			normalized_3d_vector;
	t_material		material;
	double			radius;
	t_shape_type	type;
}					t_shape;

typedef struct s_intersection
{
	double		t;
	double		n1;
	double		n2;
	t_tuple		point;
	t_tuple 	over_point; // for reflection
	t_tuple 	under_point; // for refraction
	t_tuple		eyev; // vector
	t_tuple		normalv; // vector
	t_shape		*object;
	int			inside;
	t_tuple		reflectv; // vector
}				t_intersection;

typedef struct	s_intersects // array of intersections
{
	int				count;
	t_intersection	*array;
}					t_intersects;

typedef struct	s_light
{
	t_tuple	position; // point
	t_tuple	intensity; // color
}			t_light;

typedef struct s_ambient
{
	double	ratio;
	t_tuple	color;
}			t_ambient;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_matrix	transform;
}				t_camera;

typedef struct	s_canvas
{
	int			width;
	int			height;
	t_tuple		**pixels;
}				t_canvas;

typedef struct s_scene
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	t_ambient			ambient;
	t_camera			camera;
	t_light				light;
	t_shape				**shapes; // The pointer-based array t_shape **shapes is retained but should be converted to a t_shape shapes[MAX_SHAPES] if a fixed number is known.
}				t_scene;

#endif
