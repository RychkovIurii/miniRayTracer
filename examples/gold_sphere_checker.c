	t_scene scene;

	// Initialize the scene
	scene.shapes = (t_shape **)calloc(4, sizeof(t_shape *));

	scene.ambient_lightning.ambient = 0.2;
	scene.ambient_lightning.color = create_color(255/255.0, 255/255.0, 255/255.0);

	t_shape *sphere = (t_shape *)calloc(1, sizeof(t_shape));
	sphere->type = SHAPE_SPHERE;
	sphere->center = point(0, 5.0, -10.0);
	sphere->radius = 2.5;
	sphere->transform = identity_matrix(4);
	sphere->material = material(create_color(1.0, 0.8, 0.0), scene.ambient_lightning.ambient, 0.3, 1.0, 300.0, PATTERN_NONE);
	sphere->material.reflective = 0.9;
	sphere->material.transparency = 0.0;
	sphere->material.refractive_index = 1.0;
	scene.shapes[0] = sphere;

	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->type = SHAPE_PLANE;
	floor->center = point(0, 0, 0);
	floor->plane_normal = vector(0, 1, 0);
	floor->transform = translation_matrix(0, -10, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = set_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	floor->material.pattern.transform = scaling_matrix(10, 10, 10);
	floor->material.reflective = 0.2;
	floor->material.transparency = 0.0;
	floor->material.refractive_index = 1.0;
	scene.shapes[1] = floor;

	t_shape *floor1 = (t_shape *)calloc(1, sizeof(t_shape));
	floor1->type = SHAPE_PLANE;
	floor1->center = point(0, 0, 0);
	floor1->plane_normal = vector(0, 1, 0);
	floor1->transform = translation_matrix(0, 12.0, 0.0); //if we a getting point x,y,z coordinates of a point in the plane: 0.0,6.0,-10.0 It's same as floor->transform = translation_matrix(0, 6.0, -10.0);
	floor1->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor1->material.pattern = set_pattern(create_color(255.0/255.0, 0.0/255.0, 0.0/255.0), create_color(255.0/255.0, 255.0/255.0, 255.0/255.0));
	floor1->material.pattern.transform = scaling_matrix(10, 10, 10);
	floor1->material.reflective = 0.2;
	floor1->material.transparency = 0.0;
	floor1->material.refractive_index = 1.0;
	scene.shapes[2] = floor1;

	scene.camera = init_camera(0.0, 6.0, 20.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(-15.0, 5.0, 5.0), create_color(1.0, 1.0, 1.0), 0.9);
