/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:26:27 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:23:36 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_out_of_bounds(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->map_height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(map->map_copy[y]))
		return (1);
	return (0);
}

static int	is_valid_walkable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	flood_fill(t_map *map, int x, int y, char **visited)
{
	char	current_char;

	if (is_out_of_bounds(map, x, y))
		return (-1);
	if (visited[y][x] == '1')
		return (0);
	current_char = map->map_copy[y][x];
	if (current_char == '1')
		return (0);
	if (is_valid_walkable_char(current_char))
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
		return (-1);
	return (0);
}
