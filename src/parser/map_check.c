
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
			if (!is_valid_map_char(map->map_copy[y][x]))
			{
				print_error(INVALID_MAP);
				return (-1);
			}
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
				// Replace player position with empty space for flood fill
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
	// NO NEED
	// // Additional check to ensure player position is properly set
	// if (map->player->player_x == -1 || map->player->player_y == -1)
	// {
	//     print_error(INVALID_MAP);
	//     return (-1);
	// }
	return (0);
}

char	**create_visited_array(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * map->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->map_height)
	{
		visited[i] = malloc(sizeof(char) * (map->map_width + 1));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j < map->map_width)
		{
			visited[i][j] = '0';
			j++;
		}
		visited[i][j] = '\0';
		i++;
	}
	return (visited);
}

int	is_at_map_edge(t_map *map, int x, int y)
{
	if (y == 0 || y == map->map_height - 1)
		return (1);
	if (x == 0)
		return (1);
	/* 
    end of current line 
    */
	if (x >= (int)ft_strlen(map->map_copy[y]) - 1)
		return (1);
	// adjacent lines -> irregular map
	if (y > 0 && x >= (int)ft_strlen(map->map_copy[y - 1]))
		return (1);
	if (y < map->map_height - 1 && x >= (int)ft_strlen(map->map_copy[y + 1]))
		return (1);
	return (0);
}

int	is_space_properly_surrounded(t_map *map, int x, int y)
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
			// Out of bounds is OK for spaces at edges
			i++;
			continue;
		}
		// Check if neighbor is beyond line length
		if (nx >= (int)ft_strlen(map->map_copy[ny]))
		{
			// Beyond line length is OK for spaces at edges
			i++;
			continue;
		}
		
		// The neighbor exists, check what it is
		char neighbor = map->map_copy[ny][nx];
		if (neighbor != '1' && neighbor != ' ')
		{
			// If neighbor is not a wall or space, then this space is problematic
			return (0);
		}
		i++;
	}
	return (1);
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

	// Check bounds
	if (y < 0 || y >= map->map_height || x < 0)
		return (-1);
	// Check if we're going out of the actual line length
	if (x >= (int)ft_strlen(map->map_copy[y]))
		return (-1);
	// If already visited
	if (visited[y][x] == '1')
		return (0);
	
	current_char = map->map_copy[y][x];
	
	// If wall, stop here
	if (current_char == '1')
		return (0);
	
	// If space, check if it's at a valid edge position
	if (current_char == ' ')
	{
		if (!is_at_map_edge(map, x, y))
			return (-1); // Space not at edge is invalid
		return (0); // Valid edge space, don't continue flood fill
	}
	
	// If empty space (walkable area)
	if (current_char == '0')
	{
		// Check if this empty space is at the map edge
		if (is_at_map_edge(map, x, y))
			return (-1); // Empty space at edge is invalid
			
		// Check for open corners around this position
		if (has_open_corner(map, x, y))
			return (-1); // Open corner detected
		
		// Mark as visited
		visited[y][x] = '1';
		
		// Continue flood fill in 4 directions (not diagonally)
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
	char	**visited;
	int		result;
	
	if (validate_all_empty_spaces(map) == -1)
	{
		print_error(UNCLOSED_MAP);
		return (-1);
	}
	visited = create_visited_array(map);
	if (!visited)
		return (-1);
	result = flood_fill(map, map->player->player_x, map->player->player_y,
			visited);
	free_visited_array(visited, map->map_height);
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
