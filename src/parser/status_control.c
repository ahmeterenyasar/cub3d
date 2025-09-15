#include "../../include/cub3d.h"

int	handle_empty_line(t_map *map, char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = skip_whitespace(line);
	if (!line[i] || line[i] == '\n' || line[i] == '\r')
	{
		if (map->map_started)
		{
			print_error(INVALID_MAP);
			return (-1);
		}
		return (0);
	}
	return (1);
}

int	handle_map_parsing(t_map *map, char *line)
{
	if (map->textures_loaded == 15 && map->colors_loaded == 3)
	{
		if (is_map_line(line))
		{
			map->map_started = 1;
			return (1);
		}
		else if (map->map_started)
		{
			print_error(INVALID_MAP);
			return (-1);
		}
		else
			return (0);
	}
	return (2);
}

int	process_element_line(t_map *map, char **split)
{
	if (ft_strncmp(split[0], "NO", 2) == 0 && ft_strlen(split[0]) == 2)
		return (take_texture_path(&map->img[0].path, split, 0, map));
	else if (ft_strncmp(split[0], "SO", 2) == 0 && ft_strlen(split[0]) == 2)
		return (take_texture_path(&map->img[1].path, split, 1, map));
	else if (ft_strncmp(split[0], "WE", 2) == 0 && ft_strlen(split[0]) == 2)
		return (take_texture_path(&map->img[2].path, split, 2, map));
	else if (ft_strncmp(split[0], "EA", 2) == 0 && ft_strlen(split[0]) == 2)
		return (take_texture_path(&map->img[3].path, split, 3, map));
	else if (ft_strncmp(split[0], "F", 1) == 0 && ft_strlen(split[0]) == 1)
		return (take_color_values(&map->floor_color, split, 0, map));
	else if (ft_strncmp(split[0], "C", 1) == 0 && ft_strlen(split[0]) == 1)
		return (take_color_values(&map->ceiling_color, split, 1, map));
	else
	{
		print_error(INVALID_FILE_VAR);
		return (-1);
	}
}

int	status_control(t_map *map, char *map_line)
{
	char	**split;
	int		empty_result;
	int		map_result;

	empty_result = handle_empty_line(map, map_line);
	if (empty_result <= 0)
		return (empty_result);
	map_result = handle_map_parsing(map, map_line);
	if (map_result != 2)
		return (map_result);
	split = ft_split(map_line, ' ');
	if (!split || !split[0] || split[0][0] == '\0')
	{
		if (split)
			free_split(split);
		return (0);
	}
	if (process_element_line(map, split) == -1)
	{
		free_split(split);
		return (-1);
	}
	free_split(split);
	return (0);
}
