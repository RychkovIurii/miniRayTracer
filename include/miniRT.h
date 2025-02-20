/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:10:16 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 14:11:43 by henbuska         ###   ########.fr       */
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

# include "libft.h"
# include "structs.h"

# define M_PI 3.14159265358979323846  // how accurate should this be?
# define EPSILON 0.0001f

# define WIDTH 300
# define HEIGHT 150

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

#endif