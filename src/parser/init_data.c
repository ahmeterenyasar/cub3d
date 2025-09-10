/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:50:36 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 17:59:46 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_data(t_map *map)
{
    int i;

    map->map_copy = NULL;
    map->map_line = NULL;
    map->map_height = 0;
    map->map_width = 0;
    map->map_started = 0;
    map->player = malloc(sizeof(t_player));
    if (map->player)
        init_player(map->player);
    
    i = 0;
    while (i < 4)
    {
        map->img[i].path = NULL;
        i++;
    }
    
    map->floor_color.r = -1;
    map->floor_color.g = -1;
    map->floor_color.b = -1;
    map->ceiling_color.r = -1;
    map->ceiling_color.g = -1;
    map->ceiling_color.b = -1;
    map->textures_loaded = 0;
    map->colors_loaded = 0;
}


void init_player(t_player *player)
{
    player->player_x = 0;
    player->player_y = 0;
    player->rot_x = 0;
    player->rot_y = 0;
    player->direction = '\0';
}

// void init_img(t_image *image)
// {

// }

