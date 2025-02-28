/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:08:11 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 13:04:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_material(t_material material)
{
	printf("Material:\n");
	printf("Color: (%f, %f, %f)\n", material.color.x,
		material.color.y, material.color.z);
	printf("Ambient: %f\n", material.ambient);
	printf("Diffuse: %f\n", material.diffuse);
	printf("Specular: %f\n", material.specular);
	printf("Shininess: %f\n", material.shininess);
	printf("has_pattern: %d\n", material.has_pattern);
	printf("reflective: %f\n", material.reflective);
	printf("transparency: %f\n", material.transparency);
	printf("refractive_index: %f\n", material.refractive_index);
	printf("\n");
}

void	print_shape(t_shape *shape)
{
	if (!shape)
		return ;
	printf("Shape Type: %d\n", shape->type);
	printf("Center: (%f, %f, %f)\n", shape->center.x,
		shape->center.y, shape->center.z);
	printf("Radius: %f\n", shape->radius);
	printf("Scale: (%f, %f, %f)\n", shape->scale.x,
		shape->scale.y, shape->scale.z);
	printf("Normalized Vector: (%f, %f, %f)\n",
		shape->normal.x,
		shape->normal.y,
		shape->normal.z);
	print_material(shape->material);
	printf("Transformation Matrix:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", shape->transform.matrix[i][j]);
		}
		printf("\n");
	}
}

void	print_shapes(t_scene *scene)
{
	int	i;

	if (!scene->shapes)
		return ;
	i = 0;
	while (i < scene->shape_count)
	{
		printf("Shape %d:\n", i);
		print_shape(&scene->shapes[i]);
		printf("\n");
		i++;
	}
}
