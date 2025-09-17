#include "cub3d.h"

int	flood_fill(t_map *map, int x, int y, char **visited)
{
	char current_char;

	if (y < 0 || y >= map->map_height || x < 0)
		return (-1);
	if (x >= (int)ft_strlen(map->map_copy[y]))
		return (-1);
	if (visited[y][x] == '1')
		return (0);
	current_char = map->map_copy[y][x];
	if (current_char == '1')
		return (0);
	// buraya bi bakçaz boşluk işlemeyle ilgili sıkıntılar var.
	if (current_char == '0' || current_char == 'N' || current_char == 'S'
		|| current_char == 'E' || current_char == 'W')
	{
		visited[y][x] = '1';
		if (flood_fill(map, x + 1, y, visited) == -1)
			return (-1);
		if (flood_fill(map, x - 1, y, visited) == -1)
			return (-1);
		if (flood_fill(map, x, y + 1, visited) == -1)
			return (-1);
		if (flood_fill(map, x, y - 1, visited) == -1)
			return (-1);
	}
	else if (current_char == ' ')
	{
		return (-1);
	}
	return (0);
}
