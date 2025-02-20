/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 14:24:52 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include "structs.h"

# define WIDTH 800
# define HEIGHT 400
# define EPSILON	0.0001f
# define DEFAULT_REMAINING 8

# define PATTERN_NONE 0
# define PATTERN_STRIPE 1
# define PATTERN_GRADIENT 2
# define PATTERN_RING 3
# define PATTERN_CHECKER 4

/** Tuple **/

t_tuple	create_color(double r, double g, double b);
t_tuple	multiply_color(t_tuple a, t_tuple b);
t_tuple	create_tuple(double x, double y, double z, double w);
t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	substract_tuple(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple a);
t_tuple	multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple	divide_tuple(t_tuple a, double scalar);


/** Vector **/

double	magnitude(t_tuple v);
t_tuple	normalize(t_tuple v);
double	dot(t_tuple a, t_tuple b);
t_tuple	cross(t_tuple a, t_tuple b);
t_tuple reflect(t_tuple in, t_tuple normal);


/** Matrix **/

t_matrix	identity_matrix(void);
int			is_matrices_equal(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_by_tuple(t_matrix a, t_tuple b);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix a);
t_matrix	translation_matrix(double x, double y, double z);
t_matrix	scaling_matrix(double x, double y, double z);
t_matrix	rotation_x_matrix(double radian);
t_matrix	rotation_y_matrix(double radian);
t_matrix	rotation_z_matrix(double radian);
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);
t_matrix3x3	submatrix(t_matrix a, int row, int column);
double		determinant3x3(t_matrix3x3 m);
double		minor_matrix(t_matrix a, int row, int column);
double		cofactor_matrix(t_matrix a, int row, int column);
double		determinant(t_matrix a);
int			is_invertible(t_matrix a);
t_matrix	inverse_matrix(t_matrix a);


/** Intersection **/

void free_intersects(t_intersects *xs);
t_intersection 	prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs);
t_intersection	*hit(t_intersects intersections);
t_intersects local_intersect_sphere(t_shape *sphere, t_ray transformed_ray);
t_intersects local_intersect_plane(t_shape *plane, t_ray transformed_ray);
t_intersects intersect(t_shape *shape, t_ray ray);
t_tuple	normal_at(t_shape *shape, t_tuple world_point);


/** Ray **/

t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		get_ray_position(t_ray ray, double t);
t_ray		transform_ray(t_ray ray, t_matrix matrix);


/** Scene **/

t_light		point_light(t_tuple position, t_tuple intensity);
t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern);
t_canvas	*create_canvas(int width, int height);
t_material default_material();
t_shape create_shape(t_shape_type type);
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up);
t_ray ray_for_pixel(t_camera camera, int px, int py);
t_canvas *render(t_camera camera, t_scene *world);
t_camera init_camera(double x, double y, double z, t_tuple forward, double fov, int hsize, int vsize);
t_light init_light(t_tuple position, t_tuple color, double brightness);
void	free_canvas(t_canvas *canvas);


/** Color **/

t_tuple	lighting(t_material material, t_shape shape, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv, int in_shadow);
t_tuple pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point);
void	insertion_sort_intersections(t_intersection *array, int count);
t_intersects intersect_scene(t_scene *world, t_ray ray);
t_tuple reflected_color(t_scene *world, t_intersection comps, int remaining);
t_tuple refracted_color(t_scene *world, t_intersection comps, int remaining);
double schlick(t_intersection comps);
t_tuple	shade_hit(t_scene *world, t_intersection comps, int remaining, t_intersects *xs);
t_tuple	color_at(t_scene *world, t_ray ray, int remaining);
int is_shadowed(t_scene world, t_tuple point);
t_pattern		set_pattern(t_tuple a, t_tuple b);


/** Mlx **/

void ft_render_scene(void* param);
void ft_hook(void* param);
t_tuple	pixel_at(t_canvas *canvas, int x, int y);
int	round_value(int value, int min, int max);


/** Utils **/
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
