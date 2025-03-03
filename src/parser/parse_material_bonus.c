/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:24 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 11:24:01 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_shininess(char *str)
{
	double	shine;

	shine = ft_atof(str);
	if (shine < 0.0 || shine > 500.0)
		return (1);
	return (0);
}

int	validate_refractive_index(char *str)
{
	double	ref;

	ref = ft_atof(str);
	if (ref < 0.0 || ref > 2.42)
		return (1);
	return (0);
}

int	validate_double(char *str)
{
	double	value;

	value = ft_atof(str);
	if (value < 0.0 || value > 1.0)
		return (1);
	return (0);
}

int	parse_pattern(char **element, t_material *material, size_t size)
{
	double	scale;
	char	**color_a;
	char	**color_b;
	
	if (ft_strcmp(element[size - 4], "none") == 0)
		material->has_pattern = PATTERN_NONE;
	if (ft_strcmp(element[size - 4], "stripe") == 0)
		material->has_pattern = PATTERN_STRIPE;
	else if (ft_strcmp(element[size - 4], "checker") == 0)
		material->has_pattern = PATTERN_CHECKER;
	else if (ft_strcmp(element[size - 4], "gradient") == 0)
		material->has_pattern = PATTERN_GRADIENT;
	else if (ft_strcmp(element[size - 4], "ring") == 0)
		material->has_pattern = PATTERN_RING;
	else
		return (error("Invalid pattern type", 1));
	color_a = validate_color(element[size - 3]);
	color_b = validate_color(element[size - 2]);
	if (!color_a || !color_b)
		return (error("Invalid pattern colors", 1));
	material->pattern.color_a = string_to_color(color_a);
	material->pattern.color_b = string_to_color(color_b);
	if (validate_double(element[size - 1]))
		return (error("Invalid pattern scale", 1));
	scale = (ft_atof(element[size - 1]));
	material->pattern.transform = scaling_matrix(scale, scale, scale);
	if (material->has_pattern == PATTERN_NONE)
		material->pattern.transform = identity_matrix();
	return (0);
}

/* 
   Parses and validates material properties from the given elements array.
   @param element: Input data from the file.
   @param material: Pointer to the material struct to update.
   @param size: Number of arguments in element array.
   @returns 0 on success, 1 on failure.
*/
int	add_material(char **element, t_material *material, size_t size)
{
	if (validate_refractive_index(element[size - 5]))
		return (error("Invalid value for refractive_index", 1));
	material->refractive_index = ft_atof(element[size - 5]);
	if (validate_double(element[size - 6]))
		return (error("Invalid value for transparency", 1));
	material->transparency = ft_atof(element[size - 6]);
	if (validate_double(element[size - 7]))
		return (error("Invalid value for reflective", 1));
	material->reflective = ft_atof(element[size - 7]);
	if (validate_shininess(element[size - 8]))
		return (error("Invalid value for shininess", 1));
	material->shininess = ft_atof(element[size - 8]);
	if (validate_double(element[size - 9]))
		return (error("Invalid value for specular", 1));
	material->specular = ft_atof(element[size - 9]);
	if (validate_double(element[size - 10]))
		return (error("Invalid value for diffuse", 1));
	material->diffuse = ft_atof(element[size - 10]);
	if (parse_pattern(element, material, size))
		return (1);
	return (0);
}
