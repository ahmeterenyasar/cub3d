#include "cub3d.h"

void	free_visited_array(char **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

void	find_width(char *line, t_map *map)
{
	static int max_width = 0;
	int len;

	len = ft_strlen(line);
	if (len > max_width)
		max_width = len;
	map->map_width = max_width;
}