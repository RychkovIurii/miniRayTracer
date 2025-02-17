/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:21:20 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/17 20:17:34 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
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

// -----------------------------------------------------------------------------

int	validate_file_ext(t_rt *rt)
{
	const char	*filename;
	const char	*dot;

	filename = rt->filename;
	dot = ft_strrchr(filename, '.');
	if(!dot)
		return(1);
	if (ft_strncmp(dot, ".rt\0", 4))
		return (1);
	return (0);
}

void	initialize_structs(char **argv, t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	rt->filename = argv[1];
	if (validate_file_ext(rt))
	{
		printf("Invalid file extension\n");
		free(rt);
		exit(EXIT_FAILURE);
	}
}

int32_t main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_rt	*rt;
	
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		exit(EXIT_FAILURE);
	initialize_structs(argv, rt);
	if (parse_file(rt))
		exit(EXIT_FAILURE);

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/*
int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		exit(EXIT_FAILURE);
	initialize_structs(argv, rt);
	return (0);
		
	//validate file
	//init_scene
	//setup_window
	//key_hook ??
	//mlx_loop
}  */
