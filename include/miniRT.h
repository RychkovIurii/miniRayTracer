/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 18:30:06 by irychkov         ###   ########.fr       */
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

# define EPSILON 0.0001f

# define WIDTH 600
# define HEIGHT 600

# define DEFAULT_REMAINING 3

# define PATTERN_NONE 0
# define PATTERN_STRIPE 1
# define PATTERN_GRADIENT 2
# define PATTERN_RING 3
# define PATTERN_CHECKER 4

# define MOVE_STEP 1.2
# define ROTATE_OBJECT_STEP 0.2
# define ROTATE_CAMERA_STEP 0.05
# define SCALE_UP 2
# define SCALE_DOWN 0.5
# define BRIGHTNESS_STEP 0.1


/******************** PARSER FOLDER **********/
// Parsing_bonus

int		parse_cone(char **element, t_rt *rt);
void	add_cone(t_rt *rt, char **coordinates, char **normal, char **colors);

// Parsing

int		parse_file(t_rt *rt);
char	*trim_extra_spaces(char *line);
int		count_lines_in_file(int fd);
int		init_scene_structs(t_rt *rt);
int		parse_element(char **element, t_rt *rt);
int		parse_ambient(char **element, t_rt *rt);
int		parse_camera(char **element, t_rt *rt);
int		parse_light(char **element, t_rt *rt);
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


/******************** MATH FOLDER **********/
// Tuple

t_tuple		create_color(double r, double g, double b);
t_tuple		multiply_color(t_tuple a, t_tuple b);
t_tuple		point(double x, double y, double z);
t_tuple		vector(double x, double y, double z);
t_tuple		add_tuple(t_tuple a, t_tuple b);
t_tuple		substract_tuple(t_tuple a, t_tuple b);
t_tuple		negate_tuple(t_tuple a);
t_tuple		multiply_tuple_scalar(t_tuple a, double scalar);
int			is_tuples_equal(t_tuple a, t_tuple b);


//Vector 

double		magnitude(t_tuple v);
double		dot(t_tuple a, t_tuple b);
t_tuple		normalize(t_tuple v);
t_tuple		cross(t_tuple a, t_tuple b);
t_tuple		reflect(t_tuple in, t_tuple normal);


// Matrix

t_matrix	identity_matrix(void);
t_tuple		multiply_matrix_by_tuple(t_matrix a, t_tuple b);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix a);
t_matrix	translation_matrix(double x, double y, double z);
t_matrix	scaling_matrix(double x, double y, double z);
t_matrix	rotation_x_matrix(double radian);
t_matrix	rotation_y_matrix(double radian);
t_matrix	rotation_z_matrix(double radian);
double		cofactor_matrix(t_matrix a, int row, int column);
double		determinant(t_matrix a);
t_matrix	inverse_matrix(t_matrix a);
void		set_matrices(t_scene *scene);
void		update_matrices(t_shape *shape, t_matrix transform);
t_matrix	combine_all_transforms(t_shape *shape);

// Ray

t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		get_ray_position(t_ray ray, double t);
t_ray		transform_ray(t_ray ray, t_matrix matrix);

/******************** LIGHT_AND_COLOR FOLDER **********/

t_pattern	set_pattern(t_tuple a, t_tuple b); // We don't use it for now
t_tuple		pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point);
t_tuple		shade_hit(t_scene *world, t_intersection comps, int remaining, t_intersects *xs);
t_tuple		lighting(t_material material, t_shape shape, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv, int in_shadow);
t_tuple		color_at(t_scene *world, t_ray ray, int remaining);


/******************** INTERSECTION FOLDER **********/

t_tuple			normal_at(t_shape *shape, t_tuple world_point);
t_intersects	local_intersect_sphere(t_shape *sphere, t_ray transformed_ray);
t_intersects	local_intersect_plane(t_shape *plane, t_ray transformed_ray);
t_intersects	local_intersect_cylinder(t_shape *cylinder, t_ray ray);
t_intersects	local_intersect_cone(t_shape *cone, t_ray ray);
t_intersects	intersect_scene(t_scene *world, t_ray ray);
t_intersection 	prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs);
t_intersection	*hit(t_intersects intersections);

/******************** KEYBOARD FOLDER **********/

void	handle_mouse_and_exit(t_scene *scene);
void	handle_camera_movement(t_scene *scene);
void	handle_object_movement(t_scene *scene);
void	handle_object_transformation(t_scene *scene);
void	handle_light_controls(t_scene *scene);



/******************** ROOT FOLDER **********/

t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern);
t_canvas	*create_canvas(int width, int height);
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up);
t_ray ray_for_pixel(t_camera camera, int px, int py, t_tuple origin);
void	render(t_camera camera, t_scene *scene);
t_camera init_camera(t_tuple from, t_tuple forward, double fov);
t_light init_light(t_tuple position, t_tuple color, double brightness);
void	free_canvas(t_canvas *canvas);




/** Mlx **/

void ft_render_scene(void* param);
t_tuple	pixel_at(t_canvas *canvas, int x, int y);
int	round_value(int value, int min, int max);


/** Utils **/

void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);


/** Debug **/

void print_shapes(t_scene *scene);


/** Keyboard **/
void ft_hook(void* param);


#endif
