/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 15:36:05 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	assign_default_material(t_material *material)
{
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 300.0;
	material->reflective = 0.5;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
}
