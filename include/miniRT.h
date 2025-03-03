/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 16:35:24 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include "structs.h"

# define EPSILON 0.0001f

# define WIDTH 500
# define HEIGHT 500

# define DEFAULT_REMAINING 5

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

int		parse_sphere_bonus(char **element, t_rt *rt);
int		parse_plane_bonus(char **element, t_rt *rt);
int		parse_cylinder_bonus(char **element, t_rt *rt);
int		parse_cone_bonus(char **element, t_rt *rt);
int		add_material(char **element, t_material *material, size_t size);
t_shape	*add_cone_bonus(t_rt *rt, t_file data);
t_shape	*add_sphere_bonus(t_rt *rt, char **coordinates, char **colors, double diameter);
t_shape	*add_plane_bonus(t_rt *rt, t_file data);
t_shape	*add_cylinder_bonus(t_rt *rt, t_file data);

// Parsing

int		parse_file(t_rt *rt);
char	*trim_extra_spaces(char *line);
int		count_lines_in_file(int fd);
int		init_scene_structs(char **lines, t_rt *rt);
int		parse_element(char **element, t_rt *rt);
int		parse_ambient(char **element, t_rt *rt);
int		parse_camera(char **element, t_rt *rt);
int		parse_light(char **element, t_rt *rt);
int		parse_sphere(char **element, t_rt *rt);
int		parse_plane(char **element, t_rt *rt);
int		parse_cylinder(char **element, t_rt *rt);
void	add_sphere(t_rt *rt, char **coordinates, char **colors, double diameter);
void	add_plane(t_rt *rt, t_file data);
void	add_cylinder(t_rt *rt, t_file data);
void	assign_default_material(t_material *material);
int		invalid_file_content(t_rt *rt);
int		validate_argument_count(char **array, int count);
t_file	validate_args(char **element, int coord_i, int normal_i, int color_i);
char	**validate_color(char *str);
char	**validate_coordinates(char *str);
char	**validate_vector(char *str);
int		validate_double(char *str, double min, double max);
double	validate_dimension(char *str);
double	ft_atof(char *str);
int		rt_atoi(char *str);
t_tuple	string_to_point(char **strings);
t_tuple	string_to_vector(char **strings);
t_tuple	string_to_color(char **strings);
void	free_array(char **array);
void	free_rt(t_rt *rt);
int		free_and_return(t_rt *rt, char **array, int ret);
int		print_clean(t_rt *rt, char *message, int ret);
void	free_arrays(char **array1, char **array2);
void	print_error(char *message);
int		error(char *message, int ret);
int		ft_strcmp(char const *s1, char const *s2);

/******************** MATH FOLDER **********/
// Tuple

t_tuple	create_color(double r, double g, double b);
t_tuple	multiply_color(t_tuple a, t_tuple b);
t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	substract_tuple(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple a);
t_tuple	multiply_tuple_scalar(t_tuple a, double scalar);
int		is_tuples_equal(t_tuple a, t_tuple b);

//Vector 

double	magnitude(t_tuple v);
double	dot(t_tuple a, t_tuple b);
t_tuple	normalize(t_tuple v);
t_tuple	cross(t_tuple a, t_tuple b);
t_tuple	reflect(t_tuple in, t_tuple normal);

// Matrix

double		determinant(t_matrix a);
double		cofactor_matrix(t_matrix a, int row, int column);
t_tuple		multiply_matrix_by_tuple(t_matrix a, t_tuple b);
t_matrix	identity_matrix(void);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix a);
t_matrix	translation_matrix(double x, double y, double z);
t_matrix	scaling_matrix(double x, double y, double z);
t_matrix	rotation_x_matrix(double radian);
t_matrix	rotation_y_matrix(double radian);
t_matrix	rotation_z_matrix(double radian);

t_matrix	inverse_matrix(t_matrix a);
void		set_matrices(t_scene *scene);
void		update_matrices(t_shape *shape, t_matrix transform);

// Ray

t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		get_ray_position(t_ray ray, double t);
t_ray		transform_ray(t_ray ray, t_matrix matrix);

/******************** LIGHT_AND_COLOR FOLDER **********/

t_pattern	set_pattern(t_tuple a, t_tuple b); // We don't use it for now
t_tuple		pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point);
t_tuple		shade_hit(t_scene *world, t_intersection comps, int remaining);
t_tuple		lighting(t_intersection comps, t_shape shape, t_light light, int in_shadow);
t_tuple		color_at(t_scene *world, t_ray ray, int remaining);

/******************** INTERSECTION FOLDER **********/

t_tuple			normal_at(t_shape *shape, t_tuple world_point);
t_intersects	local_intersect_sphere(t_shape *sphere, t_ray transformed_ray);
t_intersects	local_intersect_plane(t_shape *plane, t_ray transformed_ray);
t_intersects	local_intersect_cylinder(t_shape *cylinder, t_ray ray);
t_intersects	local_intersect_cone(t_shape *cone, t_ray ray);
t_intersects	intersect_scene(t_scene *world, t_ray ray);
t_intersection	prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs);
t_intersects	intersect(t_shape *shape, t_ray ray);
t_intersection	*hit(t_intersects intersections);
int				check_cone_cap(t_ray ray, double t, t_shape cone, double y);

/******************** KEYBOARD FOLDER **********/

void	handle_mouse_and_exit(t_scene *scene);
void	handle_camera_movement(t_scene *scene);
void	handle_object_movement(t_scene *scene);
void	handle_object_transformation(t_scene *scene);
void	handle_light_controls(t_scene *scene);

/******************** ROOT FOLDER **********/
// Camera

t_camera	init_camera(t_tuple from, t_tuple forward, double fov);

// Mlx

void	ft_hook(void *param);

// Scene

void	ft_render_scene(void *param);
t_ray	ray_for_pixel(t_camera camera, int px, int py, t_tuple origin);

// Init

t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern);
t_light		init_light(t_tuple position, t_tuple color, double brightness);
void		init_scene_pixels(t_scene *scene, int height, int width);
void		initialize_structs(char **argv, t_rt *rt);

/******************** UTILS FOLDER **********/

void	ft_lstclear_safe(t_list **lst);
void	ft_lstremove(t_list **lst, void *content);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int argument);
void	*ft_calloc(size_t count, size_t size);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char	*str);

int		validate_file_ext(t_rt *rt);
/** Debug **/
void	print_shapes(t_scene *scene);
void	print_parsed_content(t_rt *rt);

#endif
