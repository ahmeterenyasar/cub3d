/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:07:32 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 14:07:36 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

int	check_player_count(int player_count)
{
	if (player_count == 0)
	{
		print_error(NO_PLAYER);
		return (-1);
	}
	else if (player_count > 1)
	{
		print_error(DUPLICATE_PLAYER);
		return (-1);
	}
	return (0);
}

void	check_is_player(t_map *map, int x, int y)
{
	char	current_char;

	current_char = map->map_copy[y][x];
	if (current_char == 'N' || current_char == 'S' || current_char == 'E'
		|| current_char == 'W')
	{
		map->player->player_count++;
		map->player->player_x = x;
		map->player->player_y = y;
		map->player->direction = current_char;
		map->map_copy[y][x] = '0';
	}
}
