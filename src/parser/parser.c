
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

int	read_map(int fd, t_map *map)
{
	int		status;
	char	**map_copy;
	int		map_height;

	map_copy = NULL;
	map_height = 0;
	while (1)
	{
		map->map_line = get_next_line(fd);
		if (!map->map_line)
			break ;
		status = status_control(map, map->map_line);
		if (status == 1)
		{
			if (add_map_line(map, &map_copy, &map_height) == -1)
			{
				free(map->map_line);
				return (-1);
			}
		}
		else if (status == -1)
		{
			free(map->map_line);
			return (-1);
		}
		free(map->map_line);
	}
	map->map_copy = map_copy;
	map->map_height = map_height;
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
		close(fd);
		return (-1);
	}
	if (!validate_all_elements_loaded(map))
		return (-1);
	if (!map->map_is_ready || map->map_height == 0)
	{
		print_error(INVALID_MAP);
		close(fd);
		return (-1);
	}
	if (process_map(map) == -1)
		return (-1);
	close(fd);
	debug_print_all_data(map);
	print_map_copy(map->map_copy, map->map_height);
	return (0);
}
