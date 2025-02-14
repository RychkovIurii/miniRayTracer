# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 13:55:25 by irychkov          #+#    #+#              #
#    Updated: 2025/02/14 15:10:45 by henbuska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = main.c parsing.c utils.c
SRC_DIR = ./src
OBJ_DIR = ./obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

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

CFLAGS = -Wall -Wextra -Werror
CC = cc

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX): $(MLX_DIR)/CMakeLists.txt
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBMLX) $(LIBFT) $(OSFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft bonus