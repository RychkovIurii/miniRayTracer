/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:24 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 15:15:39 by henbuska         ###   ########.fr       */
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
	if (ref < 0.0 || ref > 3.0)
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

/* 
   Parses and validates material properties from the given elements array.
   @param element: Input data from the file.
   @param material: Pointer to the material struct to update.
   @param size: Number of arguments in element array.
   @returns 0 on success, 1 on failure.
*/
int	add_material(char **element, t_material *material, size_t size)
{
	if (validate_refractive_index(element[size - 1]))
		return (error("Invalid value for refractive_index", 1));
	material->refractive_index = ft_atof(element[size - 1]);
	if (validate_double(element[size - 2]))
		return (error("Invalid value for transparency", 1));
	material->transparency = ft_atof(element[size - 2]);
	if (validate_double(element[size - 3]))
		return (error("Invalid value for reflective", 1));
	material->reflective = ft_atof(element[size - 3]);
	if (validate_shininess(element[size - 4]))
		return (error("Invalid value for shininess", 1));
	material->shininess = ft_atof(element[size - 4]);
	if (validate_double(element[size - 5]))
		return (error("Invalid value for specular", 1));
	material->specular = ft_atof(element[size - 5]);
	if (validate_double(element[size - 6]))
		return (error("Invalid value for diffuse", 1));
	material->diffuse = ft_atof(element[size - 6]);
	return (0);
}
