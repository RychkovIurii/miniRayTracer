/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 18:42:26 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
}	t_quadratic;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_matrix3x3
{
	double	matrix[3][3];
}	t_matrix3x3;

typedef struct s_matrix
{
	double	matrix[4][4];
}			t_matrix;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_pattern
{
	t_tuple		color_a;
	t_tuple		color_b;
	t_matrix	transform;
}	t_pattern;

typedef struct s_material
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

typedef struct s_color
{
	t_tuple		ambient;
	t_tuple		diffuse;
	t_tuple		specular;
}	t_color;

typedef struct s_light
{
	double	brightness;
	t_tuple	position;
	t_tuple	intensity;
	t_tuple	color;
	int		id;
}	t_light;

typedef struct s_ambient
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
}	t_camera;

typedef enum e_shape_type
{
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_CYLINDER,
	SHAPE_CONE
}	t_shape_type;

typedef struct s_shape
{
	double			radius;
	double			min;
	double			max;
	double			height;
	int				closed;
	int				selected;
	t_tuple			scale;
	t_tuple			center;
	t_tuple			point_on_plane;
	t_tuple			normal;
	t_matrix		transform;
	t_matrix		transform_inv;
	t_matrix		transpose_inv;
	t_material		material;
	t_shape_type	type;
}	t_shape;

typedef struct s_intersection
{
	double		t;
	double		n1;
	double		n2;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		under_point;
	t_tuple		eyev;
	t_tuple		normalv;
	t_shape		*object;
	t_tuple		reflectv;
}	t_intersection;

typedef struct s_intersects
{
	int				count;
	t_intersection	*array;
}	t_intersects;

typedef struct s_scene
{
	int				shape_count;
	int				num_objects;
	int				needs_render;
	int				mouse_x;
	int				mouse_y;
	int				width;
	int				height;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_shape			*shapes;
	t_tuple			**pixels;
}	t_scene;

typedef struct s_file
{
	char	**coordinates;
	char	**normal;
	char	**colors;
}	t_file;

typedef struct s_rt
{
	char		*filename;
	int			element_count;
	char		**elements;
	t_scene		*scene;
}	t_rt;

#endif
