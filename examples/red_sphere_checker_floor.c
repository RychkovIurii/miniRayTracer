/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_sphere_checker_floor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:30:39 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/19 22:48:29 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_scene scene;

	// Initialize the scene
	scene.shapes = (t_shape **)calloc(3, sizeof(t_shape *));

	scene.ambient_lightning.ambient = 0.2;
	scene.ambient_lightning.color = create_color(255/255.0, 255/255.0, 255/255.0);

	t_shape *sphere = (t_shape *)calloc(1, sizeof(t_shape));
	sphere->type = SHAPE_SPHERE;
	sphere->center = point(0, 5.0, -10.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix(4);
	sphere->material = material(create_color(0.49, 0.051, 0.051), scene.ambient_lightning.ambient, 0.8, 0.4, 150.0, PATTERN_NONE);
	//sphere->material.reflective = 0.1;
	/* sphere->material.transparency = 0.3;
	sphere->material.refractive_index = 1.5; */
	scene.shapes[0] = sphere;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, 0, 0);
	floor->plane_normal = vector(0, 1, 0);
	floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	//floor->material.reflective = 0.2;
	scene.shapes[1] = floor;

	scene.camera = init_camera(0.0, 5.0, 20.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(-20.0, 1.0, 0.0), create_color(1.0, 1.0, 1.0), 0.9);
