// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

/* 
Common materials and their refractive indices:

Vacuum: 1
Air: 1.00029
Water: 1.333
Glass: 1.52
Diamond: 2.417
 */

#include "miniRT.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_scene(void* param)
{
	t_scene *scene = (t_scene *)param;
	t_canvas *canvas = render(scene->camera, scene);

	for (int y = 0; y < scene->camera.vsize; ++y)
	{
		for (int x = 0; x < scene->camera.hsize; ++x)
		{
			t_tuple color = pixel_at(canvas, x, y);
			int mlx_color = ft_pixel(
				round_value((int)(color.x * 255), 0, 255),
				round_value((int)(color.y * 255), 0, 255),
				round_value((int)(color.z * 255), 0, 255),
				255
			);
			mlx_put_pixel(scene->image, x, y, mlx_color);
		}
	}

	free_canvas(canvas);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

t_camera init_camera(double x, double y, double z, t_tuple forward, double fov, int hsize, int vsize) {
	t_camera camera;
	double		half_view;
	double		aspect;

	//If forward is collinear with (0,1,0), the cross() product in view_transform() may fail.
	//Solution: Ensure forward is never (0,1,0) or (0,-1,0).

	// Camera position
	t_tuple from = point(x, y, z);

	// Default up vector (assuming world up is (0,1,0))
	t_tuple up = vector(0.0, -1.0, 0.0);

	// Assign field of view
	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.field_of_view = fov;
	camera.transform = identity_matrix(4);

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
	light.intensity = multiply_tuple_scalar(color, brightness);

	return light;
}

int32_t main(void)
{
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
	floor->transform = translation_matrix(0, -10, 0.0);
	floor->material = material(create_color(0.0/255.0, 0/255.0, 255.0/255.0), scene.ambient_lightning.ambient, 0.8, 0.4, 100.0, PATTERN_CHECKER);
	floor->material.pattern = checker_pattern(create_color(255.0/255.0, 255.0/255.0, 255.0/255.0), create_color(0.0/255.0, 0.0/255.0, 0.0/255.0));
	//floor->material.reflective = 0.2;
	scene.shapes[1] = floor;

	scene.camera = init_camera(0.0, 5.0, 20.0, vector(0.0, 0.0, -1.0), 100.0, WIDTH, HEIGHT);

	scene.light = init_light(point(-20.0, 1.0, 0.0), create_color(1.0, 1.0, 1.0), 0.7);

	// Gotta error check this stuff
	if (!(scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(scene.image = mlx_new_image(scene.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(scene.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(scene.mlx, scene.image, 0, 0) == -1)
	{
		mlx_close_window(scene.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(scene.mlx, ft_render_scene, &scene);
	//mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);

	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (EXIT_SUCCESS);
}
