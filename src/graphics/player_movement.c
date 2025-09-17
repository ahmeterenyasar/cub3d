/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igurses <igurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/17 16:07:21 by igurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	init_player_direction(t_player *player)
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
	else if (player->direction == 'E')
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
	player->pos_x = (double)player->player_x + 0.5;
	player->pos_y = (double)player->player_y + 0.5;
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos_x + game->map->player->dir_x * MOVE_SPEED;
	new_y = game->map->player->pos_y + game->map->player->dir_y * MOVE_SPEED;
	if (game->map->map_copy[(int)new_y][(int)game->map->player->pos_x] != '1')
		game->map->player->pos_y = new_y;
	if (game->map->map_copy[(int)game->map->player->pos_y][(int)new_x] != '1')
		game->map->player->pos_x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos_x - game->map->player->dir_x * MOVE_SPEED;
	new_y = game->map->player->pos_y - game->map->player->dir_y * MOVE_SPEED;
	if (game->map->map_copy[(int)new_y][(int)game->map->player->pos_x] != '1')
		game->map->player->pos_y = new_y;
	if (game->map->map_copy[(int)game->map->player->pos_y][(int)new_x] != '1')
		game->map->player->pos_x = new_x;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos_x - game->map->player->plane_x * MOVE_SPEED;
	new_y = game->map->player->pos_y - game->map->player->plane_y * MOVE_SPEED;
	if (game->map->map_copy[(int)new_y][(int)game->map->player->pos_x] != '1')
		game->map->player->pos_y = new_y;
	if (game->map->map_copy[(int)game->map->player->pos_y][(int)new_x] != '1')
		game->map->player->pos_x = new_x;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos_x + game->map->player->plane_x * MOVE_SPEED;
	new_y = game->map->player->pos_y + game->map->player->plane_y * MOVE_SPEED;
	if (game->map->map_copy[(int)new_y][(int)game->map->player->pos_x] != '1')
		game->map->player->pos_y = new_y;
	if (game->map->map_copy[(int)game->map->player->pos_y][(int)new_x] != '1')
		game->map->player->pos_x = new_x;
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
