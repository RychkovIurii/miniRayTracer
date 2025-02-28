/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 13:14:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef struct	s_quadratic
{
	double	a;
	double	b;
	double	c;
}	t_quadratic;

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
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	int			has_pattern;
	t_tuple		color;
	t_pattern	pattern;
}			t_material;

typedef struct	s_light
{
	double	brightness;
	t_tuple	position;
	t_tuple	intensity;
	t_tuple	color;
	int		id;
}	t_light;

typedef struct	s_ambient
{
	double	ratio;
	t_tuple	color;
	int		id;
}	t_ambient;

typedef struct s_camera
{
	double		pixel_size;
	double		half_width;
	double		half_height;
	double		field_of_view;
	int			id;
	t_matrix	transform;
	t_matrix	transform_inv;
	t_tuple		view_point;
	t_tuple		normal;
}				t_camera;

typedef enum { SHAPE_SPHERE, SHAPE_PLANE, SHAPE_CYLINDER, SHAPE_CONE } t_shape_type;

typedef struct	s_shape
{
	double		radius;
	double		min;
	double		max;
	double		height;
	bool		closed;
	t_tuple		scale;
	t_tuple		center;
	t_tuple		point_on_plane;
	t_tuple		normal;
	t_matrix	transform;
	t_matrix	transform_inv;
	t_matrix	transpose_inv;
	t_material	material;
	t_shape_type		type;
	int			selected;
}	t_shape;

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
	t_tuple		reflectv; // vector
}				t_intersection;

typedef struct	s_intersects // array of intersections
{
	int				count;
	t_intersection	*array;
}					t_intersects;


typedef struct	s_canvas
{
	int			width;
	int			height;
	t_tuple		**pixels;
}				t_canvas;

typedef struct s_scene
{
	int				shape_count;
	int				num_objects;
	//int			max_objects;;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_shape			*shapes;
	int 			needs_render;
	t_tuple			**pixels;
	int				mouse_x;
	int				mouse_y;
}				t_scene;

typedef struct	s_rt
{
	//mlx_t	*mlx;
	//t_image	*image;
	char		*filename;
	char		**elements;
	int			element_count;
	t_scene		*scene;
}	t_rt;

#endif
