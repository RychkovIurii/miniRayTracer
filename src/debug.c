/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:08:11 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 19:15:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_elements(char **elements) // We don't use it for now
{
	int	i;

	i = 0;
	while (elements[i])
	{
		printf("%s\n", elements[i]);
		i++;
	}
}

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

void	print_parsed_content(t_rt *rt)
{
	printf("***Ambient***\n");
	printf("Ambient ratio: %f\n", rt->scene->ambient.ratio);
	printf("Ambient color: %f, %f, %f\n", rt->scene->ambient.color.x, rt->scene->ambient.color.y, rt->scene->ambient.color.z);
	printf("***Camera***\n");
	printf("Camera view point: %f, %f, %f\n", rt->scene->camera.view_point.x, rt->scene->camera.view_point.y, rt->scene->camera.view_point.z);
	printf("Camera normal vector: %f, %f, %f\n", rt->scene->camera.normal.x, rt->scene->camera.normal.y, rt->scene->camera.normal.z);
	printf("Camera fow: %f\n", rt->scene->camera.field_of_view);
	printf("***Light***\n");
	printf("Light point: %f, %f, %f\n", rt->scene->light.position.x, rt->scene->light.position.y, rt->scene->light.position.z);
	printf("Light brightness: %f\n", rt->scene->light.brightness);
	printf("Light color: %f, %f, %f\n", rt->scene->light.color.x, rt->scene->light.color.y, rt->scene->light.color.z);
	printf("***Shapes***\n");
	printf("Shape count: %d\n", rt->scene->shape_count);
	int i = 0;
	while (i < rt->scene->shape_count)
	{
		t_shape	shape = rt->scene->shapes[i];
		if (shape.type == SHAPE_SPHERE)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Sphere center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Sphere radius: %f\n", shape.radius);
			printf("Sphere color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Sphere diffuse: %f\n", shape.material.diffuse);
			printf("Sphere specular: %f\n", shape.material.specular);
			printf("Sphere shininess: %f\n", shape.material.shininess);
			printf("Sphere reflective: %f\n", shape.material.reflective);
			printf("Sphere transparency: %f\n", shape.material.transparency);
			printf("Sphere refractive index: %f\n", shape.material.refractive_index);
			printf("Sphere pattern: %d\n", shape.material.has_pattern);
			printf("Sphere pattern color a: %f, %f, %f\n", shape.material.pattern.color_a.x, shape.material.pattern.color_a.y, shape.material.pattern.color_a.z);
			printf("Sphere pattern color b: %f, %f, %f\n", shape.material.pattern.color_b.x, shape.material.pattern.color_b.y, shape.material.pattern.color_b.z);
		}
		else if (shape.type == SHAPE_PLANE)
		{
			printf("Shape type: %d\n", rt->scene->shapes[i].type);
			printf("Plane center: %f, %f, %f\n", shape.point_on_plane.x, shape.point_on_plane.y, shape.point_on_plane.z);
			printf("Plane normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Plane color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Plane diffuse: %f\n", shape.material.diffuse);
			printf("Plane specular: %f\n", shape.material.specular);
			printf("Plane shininess: %f\n", shape.material.shininess);
			printf("Plane reflective: %f\n", shape.material.reflective);
			printf("Plane refractive index: %f\n", shape.material.refractive_index);
			printf("Plane transparency: %f\n", shape.material.transparency);
			printf("Plane pattern: %d\n", shape.material.has_pattern);
			printf("Plane pattern color a: %f, %f, %f\n", shape.material.pattern.color_a.x, shape.material.pattern.color_a.y, shape.material.pattern.color_a.z);
			printf("Plane pattern color b: %f, %f, %f\n", shape.material.pattern.color_b.x, shape.material.pattern.color_b.y, shape.material.pattern.color_b.z);
		}
		else if (shape.type == SHAPE_CYLINDER)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Cylinder center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Cylinder normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Cylinder radius: %f\n", shape.radius);
			printf("Cylinder height: %f\n", shape.height);
			printf("Cylinder color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Cylinder diffuse: %f\n", shape.material.diffuse);
			printf("Cylinder specular: %f\n", shape.material.specular);
			printf("Cylinder shininess: %f\n", shape.material.shininess);
			printf("Cylinder reflective: %f\n", shape.material.reflective);
			printf("Cylinder transparency: %f\n", shape.material.transparency);
			printf("Cylinder refractive index: %f\n", shape.material.refractive_index);
			printf("Cylinder pattern: %d\n", shape.material.has_pattern);
			printf("Cylinder pattern color a: %f, %f, %f\n", shape.material.pattern.color_a.x, shape.material.pattern.color_a.y, shape.material.pattern.color_a.z);
			printf("Cylinder pattern color b: %f, %f, %f\n", shape.material.pattern.color_b.x, shape.material.pattern.color_b.y, shape.material.pattern.color_b.z);
		}
		else if (shape.type == SHAPE_CONE)
		{
			printf("Shape type: %d\n", shape.type);
			printf("Cone center: %f, %f, %f\n", shape.center.x, shape.center.y, shape.center.z);
			printf("Cone normal:%f, %f, %f\n", shape.normal.x, shape.normal.y, shape.normal.z);
			printf("Cone radius: %f\n", shape.radius);
			printf("Cone height: %f\n", shape.height);
			printf("Cone color: %f, %f, %f\n", shape.material.color.x, shape.material.color.y, shape.material.color.z);
			printf("Cone diffuse: %f\n", shape.material.diffuse);
			printf("Cone specular: %f\n", shape.material.specular);
			printf("Cone shininess: %f\n", shape.material.shininess);
			printf("Cone reflective: %f\n", shape.material.reflective);
			printf("Cone transparency: %f\n", shape.material.transparency);
			printf("Cone refractive index: %f\n", shape.material.refractive_index);
			printf("Cone pattern: %d\n", shape.material.has_pattern);
			printf("Cone pattern color a: %f, %f, %f\n", shape.material.pattern.color_a.x, shape.material.pattern.color_a.y, shape.material.pattern.color_a.z);
			printf("Cone pattern color b: %f, %f, %f\n", shape.material.pattern.color_b.x, shape.material.pattern.color_b.y, shape.material.pattern.color_b.z);
		}
		i++;
	}
}