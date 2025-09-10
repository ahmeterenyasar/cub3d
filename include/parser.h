/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:50:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 16:11:332 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>

typedef struct s_img
{
    char *path;
} t_img;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_player
{
    int player_x;
    int player_y;
    int rot_x;
    int rot_y;
    char direction; // N, S, E, W
} t_player;

typedef struct s_map
{
    char **map_copy;
    char *map_line;
    int map_height;
    int map_width;
    int map_started; // Flag to track if map parsing has begun
    t_player *player;
    t_img img[4]; // NO, SO, WE, EA
    t_color floor_color;
    t_color ceiling_color;
    int textures_loaded; // bitmask for loaded textures
    int colors_loaded; // bitmask for loaded colors
} t_map;



#endif