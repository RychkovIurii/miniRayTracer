/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:20:58 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/25 14:32:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Function to create a point light source.
** @param position: The position(point) of the light source.
** @param intensity: The intensity(color) of the light source.
** @return The struct of the light source.
*/
t_light		point_light(t_tuple position, t_tuple intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess, int has_pattern)
{
	t_material material;

	material.color = color;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	material.has_pattern = has_pattern;
	material.reflective = 0.0;
	material.transparency = 0.0;
	material.refractive_index = 1.0;
	return (material);
}

/* This function creates a canvas with the given width and height. */
/* t_canvas	*create_canvas(int width, int height)
{
	t_canvas	*canvas;
	int			i;
	int			j;

	canvas = (t_canvas *)calloc(1, sizeof(t_canvas));
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = (t_tuple **)calloc(height, sizeof(t_tuple *));
	i = 0;
	while (i < height)
	{
		canvas->pixels[i] = (t_tuple *)calloc(width, sizeof(t_tuple));
		j = 0;
		while (j < width)
		{
			canvas->pixels[i][j] = create_color(0, 0, 0);
			j++;
		}
		i++;
	}
	return (canvas);
} */

/* This function frees the memory allocated for the canvas. */
/*
void	free_canvas(t_canvas *canvas)
{
	int i;

	i = 0;
	while (i < canvas->height)
	{
		free(canvas->pixels[i]);
		i++;
	}
	free(canvas->pixels);
	free(canvas);
} */

t_material default_material()
{
	t_material mat;
	mat.color = create_color(1, 1, 1);
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200.0;
	mat.has_pattern = 0;
	mat.reflective = 0.0;
	return (mat);
}

t_shape create_shape(t_shape_type type)
{
	t_shape	shape;

	shape.transform = identity_matrix();
	shape.material = default_material();
	shape.type = type;
	shape.center = point(0, 0, 0);
	shape.radius = 1;
	return (shape);
}

t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward = normalize(substract_tuple(to, from));
	if (fabs(dot(forward, up)) >= (1.0 - EPSILON))
	{
		if (fabs(forward.y) >= (1.0 - EPSILON))
			up = vector(1, 0, 0); // If forward is vertical, use (1,0,0)
		else
			up = vector(0, 1, 0); // Otherwise, use (0,1,0)
	}
	t_tuple upn = normalize(up);
	t_tuple left = cross(forward, upn);
	t_tuple true_up = cross(left, forward);

	t_matrix orientation;
	ft_bzero(&orientation, sizeof(t_matrix));
	orientation.matrix[0][0] = left.x;
	orientation.matrix[0][1] = left.y;
	orientation.matrix[0][2] = left.z;
	orientation.matrix[0][3] = 0;
	orientation.matrix[1][0] = true_up.x;
	orientation.matrix[1][1] = true_up.y;
	orientation.matrix[1][2] = true_up.z;
	orientation.matrix[1][3] = 0;
	orientation.matrix[2][0] = -forward.x;
	orientation.matrix[2][1] = -forward.y;
	orientation.matrix[2][2] = -forward.z;
	orientation.matrix[2][3] = 0;
	orientation.matrix[3][0] = 0;
	orientation.matrix[3][1] = 0;
	orientation.matrix[3][2] = 0;
	orientation.matrix[3][3] = 1;

	t_matrix translation = translation_matrix(-from.x, -from.y, -from.z);
	return multiply_matrices(orientation, translation);
}

/* This function writes a color to the pixel at the given coordinates. */
/* void write_pixel(t_canvas *canvas, int x, int y, t_tuple color)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		canvas->pixels[y][x] = color;
	}
} */


t_ray ray_for_pixel(t_camera camera, int px, int py, t_tuple origin)
{
	double xoffset = (px + 0.5) * camera.pixel_size;
	double yoffset = (py + 0.5) * camera.pixel_size;

	double world_x = camera.half_width - xoffset;
	double world_y = camera.half_height - yoffset;


	t_tuple pixel = multiply_matrix_by_tuple(camera.transform_inv, point(world_x, world_y, -1));
	t_tuple direction = normalize(substract_tuple(pixel, origin));

	return create_ray(origin, direction);
}

void	render(t_camera camera, t_scene *scene)
{
	t_tuple origin;

	camera.transform_inv = inverse_matrix(camera.transform);
	origin = multiply_matrix_by_tuple(camera.transform_inv, point(0, 0, 0));
	for (int y = 0; y < camera.vsize; y++)
	{
		for (int x = 0; x < camera.hsize; x++)
		{
			t_ray ray = ray_for_pixel(camera, x, y, origin);
			scene->pixels[y][x] = color_at(scene, ray, DEFAULT_REMAINING);
		}
	}
}

t_camera init_camera(double x, double y, double z, t_tuple forward, double fov, int hsize, int vsize)
{
	t_camera camera;
	double		half_view;
	double		aspect;

	// Camera position
	t_tuple from = point(x, y, z);
	t_tuple up = vector(0.0, -1.0, 0.0);

	// Assign field of view
	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.field_of_view = fov;

	half_view = tan(camera.field_of_view / 2);
	aspect = (double)camera.hsize / (double)camera.vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / camera.hsize;

	// Compute the view transformation matrix
	camera.transform = view_transform(from, add_tuple(from, forward), up);

	return camera;
}

t_light init_light(t_tuple position, t_tuple color, double brightness)
{
	t_light light;

	light.position = position;
	light.color = color;
	light.brightness = brightness;
	light.intensity = multiply_tuple_scalar(color, brightness);

	return light;
}
