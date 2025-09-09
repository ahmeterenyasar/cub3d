/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:56:03 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 17:59:44 by ayasar           ###   ########.fr       */
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
void take_texture_path(char **path, char **line);

/* Utils*/
int ft_strlen_for_map(char *map);

#endif
