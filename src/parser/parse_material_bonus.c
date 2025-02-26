/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:24 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/26 16:07:33 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_material(char **element, t_rt *rt)
{
	double	specular;
	double	diffuse;
	double	shininess;
	double	reflective;
	double	refractive_index;
	double	transparency;
	size_t	size;

	transparency = validate_ratio(element[size - 6]);
	if (transparency == -1)
		return (error("Invalid value for transparency", 1));
	rt->scene->material.transparency = transparency;
	refractive_index = validate_ratio(element[size - 5]);
	if (refractive_index == -1)
		return (error("Invalid value for refractive_index", 1));
	rt->scene->material.refractive_index = refractive_index;
	reflective = validate_ratio(element[size - 6]);
	if (reflective == -1)
		return (error("Invalid value for reflective", 1));
	rt->scene->material.reflective = reflective;
	if (shininess == -1)
		return (error("Invalid value for shininess", 1));
	rt->scene->material.shininess = shininess;
	if (diffuse == -1)
		return (error("Invalid value for diffuse", 1));
	rt->scene->material.diffuse = diffuse;
	if (specular == -1)
		return (error("Invalid value for specular", 1));
	rt->scene->material.specular = specular;
	return (0);
}
