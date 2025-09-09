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

typedef struct s_player
{
    int player_x;
    int player_y;
    int rot_x;
    int rot_y;
} t_player;

typedef struct s_map
{
    char **map_copy;
    char *map_line;
    int map_height;
    int map_width;
    t_player *player;
    t_img img[5];
} t_map;



#endif