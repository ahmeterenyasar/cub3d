# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cub3D <cub3D@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 00:00:00 by cub3D             #+#    #+#              #
#    Updated: 2025/08/27 00:00:00 by cub3D            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = src/utils/libft
GNL_DIR = src/utils/get_next_line
MLX_DIR = minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lbsd

# Source files
SRCS = main.c \
       $(SRC_DIR)/utils/validate_arguments.c \
       $(SRC_DIR)/utils/utils.c \
       $(SRC_DIR)/utils/free.c \
       $(SRC_DIR)/utils/map_utils.c \
       $(SRC_DIR)/utils/player_utils.c \
	   $(SRC_DIR)/utils/rgb_utils.c \
	   $(SRC_DIR)/parser/parser.c \
	   $(SRC_DIR)/parser/init_data.c \
	   $(SRC_DIR)/parser/status_control.c \
	   $(SRC_DIR)/parser/map_check.c \
	   $(SRC_DIR)/parser/texture_and_rgb.c \
	   $(SRC_DIR)/parser/flood_fill.c \
	   $(SRC_DIR)/parser/prepare_line.c \
	   $(SRC_DIR)/parser/validate_texture_file.c \
	   $(SRC_DIR)/graphics/graphics.c \
	   $(SRC_DIR)/graphics/events.c \
	   $(SRC_DIR)/graphics/render.c \
	   $(SRC_DIR)/graphics/player_movement.c \
	   $(SRC_DIR)/graphics/raycasting.c \
	   $(SRC_DIR)/graphics/direction_and_rotation.c \
	   $(SRC_DIR)/graphics/init_graphics.c \
	   $(SRC_DIR)/graphics/calculations.c \

# Get Next Line files
GNL_SRCS = $(GNL_DIR)/get_next_line.c \
           $(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
GNL_OBJS = $(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJ_DIR)/gnl/%.o)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

# Rules
all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "$(BLUE)Building minilibx...$(NC)"
	@make -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(GNL_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/gnl/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
