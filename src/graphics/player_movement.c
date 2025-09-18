/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 16:45:51 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
