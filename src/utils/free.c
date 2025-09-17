

#include "../../include/cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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

void	free_map_data(t_map *map)
{
	int	i;

	if (!map)
		return ;
	
	// Free texture paths
	i = 0;
	while (i < 4)
	{
		if (map->img[i].path)
		{
			free(map->img[i].path);
			map->img[i].path = NULL;
		}
		i++;
	}
	
	// Free map copy (2D array)
	if (map->map_copy)
	{
		i = 0;
		while (i < map->map_height)
		{
			if (map->map_copy[i])
				free(map->map_copy[i]);
			i++;
		}
		free(map->map_copy);
		map->map_copy = NULL;
	}
	
	// Free player
	if (map->player)
	{
		free(map->player);
		map->player = NULL;
	}
}
