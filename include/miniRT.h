/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/17 20:26:05 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include "libft.h"

#define M_PI 3.14159265358979323846  // how accurate should this be?
#define EPSILON 0.00001

#define WIDTH 512
#define HEIGHT 512

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include <float.h>

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
	double	data[4][4];
}	t_matrix;

typedef struct	s_ambient
{
	double	ratio;
	t_tuple	color;
}	t_ambient;

typedef struct	s_light
{
	t_tuple	position;
	t_tuple	intensity;
}	t_light;

typedef struct	s_camera
{
	double		hsize;
	double		vsize;
	double		field_of_view;
	double		half_width;
	double		half_height;
	t_matrix	transform;
	t_tuple		view_point;
	t_tuple		normal;
}	t_camera;

typedef struct	s_material
{
	t_tuple		color;
	double		diffuse;
	double		specular;
	double		shininess;
	//t_pattern	pattern;
}	t_material;

typedef enum e_type
{
	SPHERE,
	PLANE,
	//CUBE,
	CYLINDER,
	CONE,
}	t_type;

typedef struct	s_shape
{
	t_matrix	transform;
	t_material	material;
	t_type		type;
	t_tuple		center;
	double		radius;
	double		min;
	double		max;
	bool		closed;
}	t_shape;

typedef struct	s_scene
{
	t_shape		*shapes;
	t_camera	*camera;
	t_light		*light;
	t_ambient	ambient;
	int			num_objects;
	int			max_objects;;
}	t_scene;

typedef struct	s_rt
{
	//mlx_t	*mlx;
	//t_image	*image;
	t_scene		*scene;
	char		*filename;
	char		**elements;
}	t_rt;

typedef struct	s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct	s_comps
{
	double		t;
	t_shape		object;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside;
	t_tuple		over_point;
}	t_comps;

typedef struct	s_intersection
{
	double		t;
	t_shape		object;
}	t_intersection;

typedef struct	s_intersections
{
	int				count;
	t_intersection	*list;
}	t_intersections;

int		parse_file(t_rt *rt);
char	*trim_extra_spaces(char *line);
int		count_lines_in_file(int fd);
int		parse_element(char **element, t_rt *rt);
double	ft_atof(char *str);
void	print_error(char *message);
void	free_array(char **array);
void	print_elements(char **elements);
int		custom_atoi(char *str);
int		validate_argument_count(char **array, int count);
int		validate_colors(char **colors);
int		validate_coordinates(char **coordinates);
int		validate_vector(char **orient_vector);
int		allocate_and_init_scene(t_rt *rt);
int		allocate_and_init_camera(t_rt *rt);

#endif