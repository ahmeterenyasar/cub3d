#include "../../include/cub3d.h"

int	find_player(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map_copy[y]))
		{
			check_is_player(map, x, y);
			x++;
		}
		y++;
	}
	if (check_player_count(map->player->player_count) == -1)
		return (-1);
	return (0);
}

char	**create_map_copy(t_map *map)
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
		while (j < (int)ft_strlen(map->map_copy[i]))
		{
			visited_map[i][j] = map->map_copy[i][j];
			j++;
		}
		while (j < map->map_width)
		{
			visited_map[i][j] = ' ';
			j++;
		}
		visited_map[i][j] = '\0';
		i++;
	}
	return (visited_map);
}

int	validate_all_empty_spaces(t_map *map)
{
	char	current_char;
	int		x;
	int		y;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map_copy[y]))
		{
			current_char = map->map_copy[y][x];
			if (current_char == '0' || current_char == 'N'
				|| current_char == 'S' || current_char == 'E'
				|| current_char == 'W')
			{
				if (is_at_map_edge(map, x, y))
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
	visited_map = create_map_copy(map);
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
	if (find_player(map) == -1)
		return (-1);
	if (validate_map_walls(map) == -1)
		return (-1);
	return (0);
}
