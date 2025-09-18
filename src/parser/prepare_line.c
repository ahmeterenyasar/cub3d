/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igurses <igurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:06:08 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 17:23:23 by igurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**resize_map_array(char **old_map, int old_height)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (old_height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < old_height)
	{
		new_map[i] = old_map[i];
		i++;
	}
	return (new_map);
}

char	*prepare_clean_line(char *original_line)
{
	char	*clean_line;

	clean_line = ft_strdup(original_line);
	if (!clean_line)
		return (NULL);
	remove_eof(clean_line);
	return (clean_line);
}

int	add_map_line(t_map *map, char ***map_copy, int *map_height)
{
	char	**new_map;
	char	*clean_line;

	map->map_is_ready = 1;
	new_map = resize_map_array(*map_copy, *map_height);
	if (!new_map)
		return (-1);
	clean_line = prepare_clean_line(map->map_line);
	if (!clean_line)
	{
		free(new_map);
		return (-1);
	}
	new_map[*map_height] = clean_line;
	if (*map_copy)
		free(*map_copy);
	*map_copy = new_map;
	(*map_height)++;
	find_width(clean_line, map);
	return (0);
}

int	process_map_line(t_map *map, int status)
{
	if (status == 1)
	{
		if (add_map_line(map, &map->map_copy, &map->map_height) == -1)
		{
			free(map->map_line);
			cleanup_get_next_line();
			return (-1);
		}
	}
	else if (status == -1)
	{
		free(map->map_line);
		cleanup_get_next_line();
		return (-1);
	}
	return (0);
}
