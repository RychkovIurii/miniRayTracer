# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 13:55:25 by irychkov          #+#    #+#              #
#    Updated: 2025/02/28 12:02:06 by irychkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = main.c\
		parser/parser.c\
		parser/parser_utils.c\
		parser/parse_element_bonus.c\
		parser/parse_element_utils.c\
		parser/parse_non_shapes.c\
		parser/parse_shapes.c\
		parser/parse_shapes_bonus.c\
		parser/add_shapes.c\
		parser/validations.c\
		parser/conversions.c\
		parser/trim_line.c\
		math/tuple.c\
		math/tuple2.c\
		math/matrix.c\
		math/matrix2.c\
		math/matrix3.c\
		math/matrix4.c\
		math/vector.c\
		math/ray.c\
		light_and_color/color.c\
		light_and_color/pattern.c\
		light_and_color/refraction_and_reflection.c \
		intersection/intersection.c\
		intersection/intersection2.c\
		intersection/normal.c\
		intersection/cone.c\
		intersection/cylinder.c\
		intersection/sphere_and_plane.c\
		intersection/prepare_computations.c\
		keyboard/keyboard.c\
		keyboard/keyboard2.c\
		utils.c\
		init.c\
		scene.c\
		camera.c\
		mlx.c\
		#parser/parse_element.c


SRC_DIR = ./src
OBJ_DIR = ./obj

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIRS = $(sort $(dir $(OBJS)))

MLX_DIR = ./MLX42

MLX_HEADER = -I $(MLX_DIR)/include

RT_HEADER = -I ./include

HEADERS = $(RT_HEADER) $(MLX_HEADER) -I$(LIBFT_DIR)

LIBMLX = $(MLX_DIR)/build/libmlx42.a

#LIBGLFW = /Users/irychkov/.brew/Cellar/glfw/3.4/lib/libglfw.3.dylib

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#OSFLAGS = $(LIBGLFW) -framework Cocoa -framework OpenGL -framework IOKit
OSFLAGS = -ldl -lglfw -pthread -lm

CFLAGS = -O3 -march=native -mtune=native -fomit-frame-pointer -DNDEBUG #-flto #-Wall -Wextra -Werror
CC = cc

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX): $(MLX_DIR)/CMakeLists.txt
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ_DIRS) $(OBJS)
	@$(CC) $(OBJS) $(LIBMLX) $(LIBFT) $(OSFLAGS) -o $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c	
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft bonus
