# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 13:55:25 by irychkov          #+#    #+#              #
#    Updated: 2025/03/05 13:45:05 by henbuska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
NAMEBONUS = miniRT_bonus

# Common sources between regular and bonus
COMMON_SRCS =	main.c\
				parser/parser.c\
				parser/parser_utils.c\
				parser/parse_element_utils.c\
				parser/parse_non_shapes.c\
				parser/validations.c\
				parser/validations2.c\
				parser/conversions.c\
				parser/conversions2.c\
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
				intersection/cone2.c\
				intersection/cylinder.c\
				intersection/sphere_and_plane.c\
				intersection/prepare_computations.c\
				keyboard/keyboard.c\
				keyboard/keyboard2.c\
				utils/libc_utils.c\
				utils/libc_utils2.c\
				utils/libc_utils3.c\
				utils/libc_utils4.c\
				utils/gnl_utils.c\
				utils/gnl.c\
				init.c\
				scene.c\
				camera.c\
				mlx.c\
				debug.c\
				free.c\
				free2.c\

# Program-specific sources
SRCS = $(COMMON_SRCS)\
				parser/parse_shapes.c\
				parser/add_shapes.c\
				parser/parse_element.c\
		

		
BONUS_SRCS = $(COMMON_SRCS)\
				parser/parse_element_bonus.c\
				parser/parse_shapes_bonus.c\
				parser/add_shapes_bonus.c\
				parser/parse_cone_bonus.c\
				parser/parse_material_bonus.c\

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ_BONUS_DIR = ./obj_bonus
MLX_DIR = ./MLX42

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_BONUS_DIR)/%.o)

# Dependency files
DEP_FILES = $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

# Create directory lists
OBJ_DIRS = $(sort $(dir $(OBJS)))
BONUS_OBJ_DIRS = $(sort $(dir $(BONUS_OBJS)))

# Compilation flags
MLX_HEADER = -I $(MLX_DIR)/include
RT_HEADER = -I ./include
HEADERS = $(RT_HEADER) $(MLX_HEADER)
LIBMLX = $(MLX_DIR)/build/libmlx42.a
#LIBGLFW = /Users/irychkov/.brew/Cellar/glfw/3.4/lib/libglfw.3.dylib
#OSFLAGS = $(LIBGLFW) -framework Cocoa -framework OpenGL -framework IOKit
OSFLAGS = -ldl -lglfw -pthread -lm -flto
CFLAGS = -O3 -march=native -mtune=native -fomit-frame-pointer -DNDEBUG -MMD -MP -MT $@ -Wall -Wextra -Werror -flto
CC = cc

all: $(LIBMLX) $(NAME)

bonus: $(LIBMLX) $(NAMEBONUS)

$(LIBMLX): $(MLX_DIR)/CMakeLists.txt
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

$(NAME): $(OBJ_DIRS) $(OBJS)
	@$(CC) $(OBJS) $(LIBMLX) $(OSFLAGS) -o $(NAME)

$(NAMEBONUS): $(OBJ_BONUS_DIRS) $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBMLX) $(OSFLAGS) -o $(NAMEBONUS)

# Compilation rules
$(OBJ_DIRS):
	@mkdir -p $@

$(OBJ_BONUS_DIRS):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

$(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@rm -rf $(MLX_DIR)/build

fclean: clean
	rm -rf $(NAME) $(NAMEBONUS)

re: fclean all

-include $(DEP_FILES)

.PHONY: all clean fclean re libmlx bonus
