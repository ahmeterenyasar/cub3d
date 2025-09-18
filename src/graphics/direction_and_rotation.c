/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_and_rotation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:48:03 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 17:17:10 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_n_and_s(t_player *player)
{
	if (player->direction == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (player->direction == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

void	direction_w_and_e(t_player *player)
{
	if (player->direction == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

void	init_player_direction(t_player *player)
{
	direction_n_and_s(player);
	direction_w_and_e(player);
	player->pos_x = (double)player->player_x + 0.5;
	player->pos_y = (double)player->player_y + 0.5;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->map->player->dir_x;
	game->map->player->dir_x = game->map->player->dir_x * cos(-ROT_SPEED)
		- game->map->player->dir_y * sin(-ROT_SPEED);
	game->map->player->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->map->player->dir_y * cos(-ROT_SPEED);
	old_plane_x = game->map->player->plane_x;
	game->map->player->plane_x = game->map->player->plane_x * cos(-ROT_SPEED)
		- game->map->player->plane_y * sin(-ROT_SPEED);
	game->map->player->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ game->map->player->plane_y * cos(-ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->map->player->dir_x;
	game->map->player->dir_x = game->map->player->dir_x * cos(ROT_SPEED)
		- game->map->player->dir_y * sin(ROT_SPEED);
	game->map->player->dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->map->player->dir_y * cos(ROT_SPEED);
	old_plane_x = game->map->player->plane_x;
	game->map->player->plane_x = game->map->player->plane_x * cos(ROT_SPEED)
		- game->map->player->plane_y * sin(ROT_SPEED);
	game->map->player->plane_y = old_plane_x * sin(ROT_SPEED)
		+ game->map->player->plane_y * cos(ROT_SPEED);
}
