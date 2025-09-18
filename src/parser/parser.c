/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:22:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:32:25 by ayasar           ###   ########.fr       */
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

int	handle_map_line_error(char *map_line)
{
	free(map_line);
	cleanup_get_next_line();
	return (-1);
}

int	process_map_line(t_map *map, int status)
{
	if (status == 1)
	{
		if (add_map_line(map, &map->map_copy, &map->map_height) == -1)
			return (handle_map_line_error(map->map_line));
	}
	else if (status == -1)
		return (handle_map_line_error(map->map_line));
	return (0);
}

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
