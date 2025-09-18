/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:09:34 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:20:48 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_img_paths(t_map *map)
{
	int	i;

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
}

void	free_map_copy(t_map *map)
{
	int	i;

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
}

void	free_player(t_map *map)
{
	if (map->player)
	{
		free(map->player);
		map->player = NULL;
	}
}

void	free_map_data(t_map *map)
{
	if (!map)
		return ;
	free_img_paths(map);
	free_map_copy(map);
	free_player(map);
}
