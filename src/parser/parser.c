/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:22:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 17:17:10 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(int fd, t_map *map)
{
	int	status;
	int	result;

	while (1)
	{
		map->map_line = get_next_line(fd);
		if (!map->map_line)
			break ;
		status = status_control(map, map->map_line);
		result = process_map_line(map, status);
		if (result == -1)
			return (-1);
		free(map->map_line);
	}
	return (0);
}

int	validate_parsed_data(t_map *map, int fd)
{
	if (!validate_all_elements_loaded(map))
	{
		cleanup_get_next_line();
		close(fd);
		return (-1);
	}
	if (!map->map_is_ready || map->map_height == 0)
	{
		print_error(INVALID_MAP);
		cleanup_get_next_line();
		close(fd);
		return (-1);
	}
	if (process_map(map) == -1)
	{
		cleanup_get_next_line();
		close(fd);
		return (-1);
	}
	return (0);
}

int	parser(char **argv, t_map *map)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		print_error(ERR_FILE_OPEN);
		return (-1);
	}
	if (read_map(fd, map) == -1)
	{
		cleanup_get_next_line();
		close(fd);
		return (-1);
	}
	if (validate_parsed_data(map, fd) == -1)
		return (-1);
	close(fd);
	return (0);
}
