/* t_scene scene;

	// Initialize the scene
	scene.shapes = (t_shape **)calloc(4, sizeof(t_shape *));

	scene.ambient.ratio = 0.2;
	scene.ambient.color = create_color(255/255.0, 255/255.0, 255/255.0);

	t_shape *sphere = (t_shape *)calloc(1, sizeof(t_shape));
	sphere->type = SHAPE_SPHERE;
	sphere->center = point(0, 6.0, -20.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix();
	sphere->material = material(create_color(1.0, 0.8, 0.0), scene.ambient.ratio, 0.3, 1.0, 300.0, PATTERN_NONE);
	sphere->material.reflective = 0.9;
	sphere->material.transparency = 0.0;
	sphere->material.refractive_index = 1.0;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, -3.0, 0);
	floor->normal = vector(0, 1, 0);
	floor->scale = vector(1, 1, 1);
	//floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient.ratio, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	floor->material.reflective = 0.2;
	floor->material.transparency = 0.0;
	floor->material.refractive_index = 0.0;
	scene.shapes[1] = floor;

	t_shape *wall = (t_shape *)calloc(1, sizeof(t_shape));
	wall->type = SHAPE_PLANE;
	wall->center = point(0, 0, 100);
	wall->normal = vector(0.0, 0, 1);
	wall->scale = vector(1, 1, 1);
	//wall->transform = translation_matrix(0, 12.0, 20.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	wall->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient.ratio, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	wall->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	wall->material.pattern.transform = scaling_matrix(20, 20, 20);
	wall->material.reflective = 0.2;
	wall->material.transparency = 0.0;
	wall->material.refractive_index = 0.0;
	scene.shapes[2] = wall;

	scene.camera = init_camera(0.0, 6.0, 15.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(0, 30.0, 30.0), create_color(1.0, 1.0, 1.0), 0.9);

	set_matrices(&scene);

	print_shapes(scene);

	// Gotta error check this stuff
	
	
	mlx_loop_hook(scene.mlx, ft_render_scene, &scene);
	mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);

	scene.light = init_light(point(-20.0, 1.0, 0.0), create_color(1.0, 1.0, 1.0), 0.7); 
	
	
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	free(scene.shapes[0]);
	free(scene.shapes[1]);
	free(scene.shapes);*/
