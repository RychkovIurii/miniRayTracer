/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 14:49:49 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>
# include <float.h>
# include <limits.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include "structs.h"

# include "libft.h"

# define M_PI 3.14159265358979323846  // how accurate should this be?
# define EPSILON 0.0001f

# define WIDTH 300
# define HEIGHT 150

# define DEFAULT_REMAINING 5

# define PATTERN_NONE 0
# define PATTERN_STRIPE 1
# define PATTERN_GRADIENT 2
# define PATTERN_RING 3
# define PATTERN_CHECKER 4

/** Parsing */

int		parse_file(t_rt *rt);
char	*trim_extra_spaces(char *line);
int		count_lines_in_file(int fd);
int		init_scene_structs(t_rt *rt);
int		parse_element(char **element, t_rt *rt);
int		parse_sphere(char **element, t_rt *rt);
int		parse_plane(char **element, t_rt *rt);
int		parse_cylinder(char **element, t_rt *rt);
void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter);
void	add_plane(t_rt *rt, char **coordinates, char **normal, char **colors);
void	add_cylinder(t_rt *rt, char **coordinates, char** normal, char **colors);
int		invalid_file_content(t_rt *rt);
int		validate_argument_count(char **array, int count);
char	**validate_color(char *str);
char	**validate_coordinates(char *str);
char	**validate_vector(char *str);
double	validate_ratio(char *str);
double	validate_dimension(char *str);
double	ft_atof(char *str);
int		rt_atoi(char *str);
t_tuple	string_to_point(char **strings);
t_tuple	string_to_vector(char **strings);
t_tuple	string_to_color(char **strings);
void	free_array(char **array);
//void	print_elements(char **elements);
void	free_rt(t_rt *rt);
int		free_and_return(t_rt *rt, char **array, int ret);
void	print_error(char *message);
int		error(char *message, int ret);
int		ft_strcmp(char const *s1, char const *s2);

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
int	is_tuples_equal(t_tuple a, t_tuple b);
int	is_point(t_tuple a);
int	is_vector(t_tuple a);


/** Vector **/

double	magnitude(t_tuple v);
t_tuple	normalize(t_tuple v);
double	dot(t_tuple a, t_tuple b);
t_tuple	cross(t_tuple a, t_tuple b);
t_tuple reflect(t_tuple in, t_tuple normal);


/** Matrix **/

t_matrix	create_matrix(int size);
t_matrix	identity_matrix(int size);
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
t_matrix	submatrix(t_matrix a, int row, int column);
double		minor_matrix(t_matrix a, int row, int column);
double		cofactor_matrix(t_matrix a, int row, int column);
double		determinant(t_matrix a);
int			is_invertible(t_matrix a);
t_matrix	inverse_matrix(t_matrix a);


/** Intersection **/

void			ft_bzero(void *s, size_t n);
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
t_tuple	pixel_at(t_canvas *canvas, int x, int y);
void	free_canvas(t_canvas *canvas);
int	round_value(int value, int min, int max);

/** Scene **/

t_light		point_light(t_tuple position, t_tuple intensity);
t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern);
t_canvas	*create_canvas(int width, int height);
t_material default_material();
t_shape create_shape(t_shape_type type);
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up);
void write_pixel(t_canvas *canvas, int x, int y, t_tuple color);
t_ray ray_for_pixel(t_camera camera, int px, int py);
t_canvas *render(t_camera camera, t_scene *world);


/** Color **/

t_tuple	lighting(t_material material, t_shape shape, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv, int in_shadow);
t_tuple pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point);
void	bubble_sort_intersections(t_intersection *array, int count);
t_intersects intersect_scene(t_scene *world, t_ray ray);
t_tuple reflected_color(t_scene *world, t_intersection comps, int remaining, t_intersects *xs);
t_tuple refracted_color(t_scene *world, t_intersection comps, int remaining, t_intersects *xs);
double schlick(t_intersection comps);
t_tuple	shade_hit(t_scene *world, t_intersection comps, int remaining, t_intersects *xs);
t_tuple	color_at(t_scene *world, t_ray ray, int remaining);
int is_shadowed(t_scene world, t_tuple point);
t_pattern		checker_pattern(t_tuple a, t_tuple b);

#endif
