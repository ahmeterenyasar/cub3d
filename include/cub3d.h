/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igurses <igurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:56:03 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/17 16:54:07 by igurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/utils/get_next_line/get_next_line.h"
# include "../src/utils/libft/libft.h"
# include "graphics.h"
# include "parser.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ERR_USAGE "Error\nUsage: ./cub3D <map.cub>"
# define ERR_FILE_EXT "Error\nFile must have .cub extension"
# define ERR_FILE_OPEN "Error\nCannot open file"
# define ERR_FILE_READ "Error\nCannot read file"
# define INVALID_FILE_VAR "Error\nIncorrect data"
# define INVALID_TEXTURE_LINE "Error\nTexture line is incorrect"
# define INVALID_COLOR_LINE "Error\nColor line is incorrect"
# define DUPLICATE_ELEMENT "Error\nDuplicate element found"
# define MISSING_ELEMENT "Error\nMissing required element"
# define INVALID_RGB "Error\nInvalid RGB values"
# define INVALID_MAP "Error\nInvalid map"
# define DUPLICATE_PLAYER "Error\nDuplicate player found"
# define NO_PLAYER "Error\nNo player found"
# define UNCLOSED_MAP "Error\nMap is not closed"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* Argument Check Function */
int		validate_arguments(int argc, char **argv);
int		validate_file_extension(char *filename);
int		validate_file_access(char *filename);
void	print_error(char *message);

/* Parser */
int		parser(char **argv, t_map *map);
int		add_map_line(t_map *map, char ***map_copy, int *map_height);
int		read_map(int fd, t_map *map);
char	*prepare_clean_line(char *original_line);
char	**resize_map_array(char **old_map, int old_height);

/* Init */
void	init_data(t_map *map);
void	init_player(t_player *player);

/* Status Check */
int		status_control(t_map *map, char *map_line);
int		handle_empty_line(t_map *map, char *line);
int		handle_map_parsing(t_map *map, char *line);
int		process_element_line(t_map *map, char **split);

/*Texture And RGB*/
int		parse_rgb_values(char *rgb_string, t_color *color);
int		take_texture_path(char **path, char **line, int texture_index,
			t_map *map);
int		is_valid_texture_extension(char *path);
int		is_texture_accessible(char *path);
int		validate_texture_file(char *path);
int		take_color_values(t_color *color, char **line, int color_type,
			t_map *map);

/* Map Check */
int		find_player(t_map *map);
int		validate_map_walls(t_map *map);
int		process_map(t_map *map);
int		flood_fill(t_map *map, int x, int y, char **visited);

/* Utils */
void	find_width(char *line, t_map *map);
int		validate_all_elements_loaded(t_map *map);
int		is_map_line(char *line);
int		is_at_map_edge(t_map *map, int x, int y);
int		check_player_count(int player_count);
void	check_is_player(t_map *map, int x, int y);
int		ft_strlen_for_map(char *map);
int		is_valid_rgb(int value);
int		skip_whitespace(char *line);
int		is_valid_map_char(char c);
void	remove_eof(char *line);
int		ft_strlen_split(char **split);
char	*ft_strjoin_split(char **split, int start);
void	free_split_with_index(char **split, int i);
void	control_split_count(char **split);
void	helper_map_copy(int j, t_map *map, char **visited_map, int i);

/* Free */
void	free_split(char **split);
void	free_visited_array(char **visited, int height);

/* Debug */
void	debug_print_all_data(t_map *map);
void	print_map_copy(char **map_copy, int map_height);

#endif
