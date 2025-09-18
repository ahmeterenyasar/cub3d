/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:02:42 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:32:26 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_data(t_map *map)
{
	int	i;

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

void	init_data(t_map *map)
{
	map->map_copy = NULL;
	map->map_line = NULL;
	map->clean_line = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->map_started = 0;
	map->map_is_ready = 0;
	map->player = malloc(sizeof(t_player));
	if (map->player)
		init_player(map->player);
	init_texture_data(map);
}

void	init_player(t_player *player)
{
	player->player_x = -1;
	player->player_y = -1;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->direction = '\0';
	player->player_count = 0;
}

void	init_img(t_game *game, t_map *map)
{
	int	i;

	game->map = map;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
}
