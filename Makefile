# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 13:55:25 by irychkov          #+#    #+#              #
#    Updated: 2025/02/18 17:52:41 by irychkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = main.c color.c intersection.c matrix.c ray.c scene.c tuple.c vector.c \
		mlx.c
SRC_DIR = ./src

OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

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

CFLAGS = -O3 -march=native #-flto #-Wall -Wextra -Werror
CC = cc

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX): $(MLX_DIR)/CMakeLists.txt
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBMLX) $(LIBFT) $(OSFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft bonus