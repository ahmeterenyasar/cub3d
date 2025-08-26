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
INCLUDES = -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files
SRCS = main.c \
       $(SRC_DIR)/utils/validate_arguments.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

# Test rules
test: $(NAME)
	@echo "$(BLUE)Testing with no arguments:$(NC)"
	@./$(NAME) || true
	@echo "$(BLUE)Testing with wrong extension:$(NC)"
	@./$(NAME) test.txt || true
	@echo "$(BLUE)Testing with non-existent file:$(NC)"
	@./$(NAME) nonexistent.cub || true

.PHONY: all clean fclean re test
