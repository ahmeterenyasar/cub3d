/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:56:03 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/11 14:10:26 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# include "parser.h"
#include "../src/utils/libft/libft.h"
#include "../src/utils/get_next_line/get_next_line.h"



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
int parser(char **argv, t_map *map);

/* Init */
void init_data(t_map *map);
void init_player(t_player *player);

/* Status Check */
int status_control(t_map *map, char *map_line);
int handle_empty_line(t_map *map, char *line);
int handle_map_parsing(t_map *map, char *line);
int process_element_line(t_map *map, char **split);
void take_texture_path(char **path, char **line, int texture_index, t_map *map);
void take_color_values(t_color *color, char **line, int color_type, t_map *map);
int parse_rgb_values(char *rgb_string, t_color *color);
int is_valid_rgb(int value);
int skip_whitespace(char *line);
int is_map_line(char *line);
int validate_all_elements_loaded(t_map *map);

/* Map Processing */
int add_map_line(t_map *map, char *line);
int process_map(t_map *map);
int find_player(t_map *map);
int validate_map_walls(t_map *map);
int flood_fill(t_map *map, int x, int y, char **visited);
char **create_visited_array(t_map *map);
void free_visited_array(char **visited, int height);
int is_valid_map_char(char c);
int calculate_map_dimensions(t_map *map);

/* Utils*/
int ft_strlen_for_map(char *map);
void free_split(char **split);


#endif
