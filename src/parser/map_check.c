#include "../../include/cub3d.h"

int	find_player(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map_copy[y]))
		{

			if (map->map_copy[y][x] == 'N' || map->map_copy[y][x] == 'S'
				|| map->map_copy[y][x] == 'E' || map->map_copy[y][x] == 'W')
			{
				player_count++;
				if (player_count > 1)
				{
					print_error(DUPLICATE_PLAYER);
					return (-1);
				}
				map->player->player_x = x;
				map->player->player_y = y;
				map->player->direction = map->map_copy[y][x];

				map->map_copy[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (player_count == 0)
	{
		print_error(NO_PLAYER);
		return (-1);
	}
	return (0);
}

char	**create_visited_array(t_map *map)
{
	char	**visited_map;
	int		i;
	int		j;

	visited_map = malloc(sizeof(char *) * map->map_height);
	if (!visited_map)
		return (NULL);
	i = 0;
	while (i < map->map_height)
	{
		visited_map[i] = malloc(sizeof(char) * (map->map_width + 1));
		if (!visited_map[i])
		{
			while (--i >= 0)
				free(visited_map[i]);
			free(visited_map);
			return (NULL);
		}
		j = 0;
		while (j < map->map_width)
		{
			visited_map[i][j] = map->map_copy[i][j];
			j++;
		}
		visited_map[i][j] = '\0';
		i++;
	}
	return (visited_map);
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

int	has_open_corner(t_map *map, int x, int y)//araştır a-m-k lazım 
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
		
		// Check if neighbor is out of bounds
		if (ny < 0 || ny >= map->map_height || nx < 0)
		{
			return (1); // Open to void
		}
		// Check if neighbor is beyond line length
		if (nx >= (int)ft_strlen(map->map_copy[ny]))
		{
			return (1); // Open to void
		}
		// Check if neighbor is a space
		if (map->map_copy[ny][nx] == ' ')
		{
			// Space is only allowed if ALL its neighbors are walls or more spaces
			if (!is_space_properly_surrounded(map, nx, ny))
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	flood_fill(t_map *map, int x, int y, char **visited)
{
	char	current_char;

	if (y < 0 || y >= map->map_height || x < 0)
		return (-1);
	if (x >= (int)ft_strlen(map->map_copy[y]))
		return (-1);
	if (visited[y][x] == '1')
		return (0);
	current_char = map->map_copy[y][x];
	if (current_char == '1')
		return (0);
	if (current_char == '0')
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
	return (0);
}

int	validate_all_empty_spaces(t_map *map)
{
	int	x, y;
	
	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map_copy[y]))
		{
			if (map->map_copy[y][x] == '0')
			{
				if (is_at_map_edge(map, x, y))
					return (-1);
				if (has_open_corner(map, x, y))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map_walls(t_map *map)
{
	char	**visited_map;
	int		result;
	
	if (validate_all_empty_spaces(map) == -1)
	{
		print_error(UNCLOSED_MAP);
		return (-1);
	}
	visited_map = create_visited_array(map);
	if (!visited_map)
		return (-1);
	result = flood_fill(map, map->player->player_x, map->player->player_y,
			visited_map);
	free_visited_array(visited_map, map->map_height);
	if (result == -1)
	{
		print_error(UNCLOSED_MAP);
		return (-1);
	}
	return (0);
}

int	process_map(t_map *map)
{
	if (map->map_height == 0)
	{
		print_error(INVALID_MAP);
		return (-1);
	}
	if (find_player(map) == -1)
		return (-1);
	if (validate_map_walls(map) == -1)
		return (-1);
	return (0);
}
