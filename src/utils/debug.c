#include "../../include/cub3d.h"

void	debug_print_all_data(t_map *map)
{
	printf("\n=== Parsed Data ===\n");
	printf("NO: %s\n", map->img[0].path ? map->img[0].path : "NULL");
	printf("SO: %s\n", map->img[1].path ? map->img[1].path : "NULL");
	printf("WE: %s\n", map->img[2].path ? map->img[2].path : "NULL");
	printf("EA: %s\n", map->img[3].path ? map->img[3].path : "NULL");
	printf("Floor RGB: %d,%d,%d\n", map->floor_color.r, map->floor_color.g,
		map->floor_color.b);
	printf("Ceiling RGB: %d,%d,%d\n", map->ceiling_color.r,
		map->ceiling_color.g, map->ceiling_color.b);
	printf("Player at: (%d, %d) facing %c\n", map->player->player_x,
		map->player->player_y, map->player->direction);
	printf("Map dimensions: %dx%d\n", map->map_width, map->map_height);
}
void	print_map_copy(char **map_copy, int map_height)
{
	int i;

	i = 0;
	while (i < map_height)
	{
		printf("%s\n", map_copy[i]);
		i++;
	}
}