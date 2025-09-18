/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:07:55 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 16:38:07 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_width(char *line, t_map *map)
{
	static int	max_width = 0;
	int			len;

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

/*
	Check if at map boundaries
	Check adjacent cells for spaces or out of bounds
*/
int	is_at_map_edge(t_map *map, int x, int y)
{
	if (y == 0 || y == map->map_height - 1)
		return (1);
	if (x == 0 || x >= (int)ft_strlen(map->map_copy[y]) - 1)
		return (1);
	if (y > 0 && (x >= (int)ft_strlen(map->map_copy[y - 1]) || map->map_copy[y
				- 1][x] == ' '))
		return (1);
	if (y < map->map_height - 1 && (x >= (int)ft_strlen(map->map_copy[y + 1])
			|| map->map_copy[y + 1][x] == ' '))
		return (1);
	if (x > 0 && map->map_copy[y][x - 1] == ' ')
		return (1);
	if (x < (int)ft_strlen(map->map_copy[y]) - 1 && map->map_copy[y][x
		+ 1] == ' ')
		return (1);
	return (0);
}

void	helper_map_copy(int j, t_map *map, char **visited_map, int i)
{
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
}
