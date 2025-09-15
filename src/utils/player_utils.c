
#include "../../include/cub3d.h"

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
	if (map->map_copy[y][x] == 'N' || map->map_copy[y][x] == 'S'
		|| map->map_copy[y][x] == 'E' || map->map_copy[y][x] == 'W')
	{
		map->player->player_count++;
		map->player->player_x = x;
		map->player->player_y = y;
		map->player->direction = map->map_copy[y][x];
	}
}
