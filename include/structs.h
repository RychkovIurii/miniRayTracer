/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/18 18:06:59 by irychkov         ###   ########.fr       */
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

typedef struct	s_matrix
{
	int		size;
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
	t_pattern	pattern;
	int			has_pattern;
	double		reflective;
	double		transparency;
	double		refractive_index;
}			t_material;

typedef enum { SHAPE_SPHERE, SHAPE_PLANE } t_shape_type;

typedef struct s_shape {
	t_matrix		transform;
	t_material		material;
	t_shape_type	type;
	t_tuple			center;
	double			radius;
	t_tuple			normalized_3d_vector;
	
}					t_shape;

typedef struct s_intersection
{
	double		t;
	t_shape		*object;
	t_tuple		point;
	t_tuple 	over_point; // for reflection
	t_tuple 	under_point; // for refraction
	t_tuple		eyev; // vector
	t_tuple		normalv; // vector
	int			inside;
	t_tuple		reflectv; // vector
	double		n1;
	double		n2;
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

typedef struct s_ambient_lightning
{
	double	ambient;
	t_tuple	color;
}			t_ambient_lightning;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_matrix	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
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
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_shape				**shapes;
}				t_scene;

#endif
