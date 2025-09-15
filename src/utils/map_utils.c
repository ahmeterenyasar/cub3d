#include "cub3d.h"

void	find_width(char *line, t_map *map)
{
	static int max_width = 0;
	int len;

	len = ft_strlen(line);
	if (len > max_width)
		max_width = len;
	map->map_width = max_width;
}

int	validate_all_elements_loaded(t_map *map)
{
	if (map->textures_loaded != 15)
	{
		print_error(MISSING_ELEMENT);
		return (0);
	}
	if (map->colors_loaded != 3)
	{
		print_error(MISSING_ELEMENT);
		return (0);
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = skip_whitespace(line);
	if (!line[i] || line[i] == '\n' || line[i] == '\r')
		return (0);
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_at_map_edge(t_map *map, int x, int y)
{
	if (y == 0 || y == map->map_height - 1)
		return (1);
	if (x == 0)
		return (1);
	if (x >= (int)ft_strlen(map->map_copy[y]) - 1)
		return (1);
	if (y > 0 && x >= (int)ft_strlen(map->map_copy[y - 1]))
		return (1);
	if (y < map->map_height - 1 && x >= (int)ft_strlen(map->map_copy[y + 1]))
		return (1);
	return (0);
}


int	has_open_corner(t_map *map, int x, int y)
{
	int	dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int	i;
	int	nx, ny;

	i = 0;
	while (i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (ny < 0 || ny >= map->map_height || nx < 0)
			return (1);
		if (nx >= (int)ft_strlen(map->map_copy[ny]))
			return (1);
		//added
		if (map->map_copy[ny][nx] == ' ')
			return (1);
		i++;
	}
	return (0);
}
