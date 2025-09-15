#include "../../include/cub3d.h"

void	take_texture_path(char **path, char **line, int texture_index,
		t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i >= 2 && line[i - 1] && line[i - 1][ft_strlen(line[i - 1])
		- 1] == '\n')
		line[i - 1][ft_strlen(line[i - 1]) - 1] = '\0';
	if (i != 2 || *path)
	{
		print_error(INVALID_TEXTURE_LINE);
		return ;
	}
	*path = ft_strdup(line[1]);
	map->textures_loaded |= (1 << texture_index);
}

int	parse_rgb_values(char *rgb_string, t_color *color)
{
	char	**rgb_split;
	int		i;

	rgb_split = ft_split(rgb_string, ',');
	if (!rgb_split)
		return (0);
	i = 0;
	while (rgb_split[i])
		i++;
	if (i != 3)
	{
		free_split(rgb_split);
		return (0);
	}
	color->r = ft_atoi(rgb_split[0]);
	color->g = ft_atoi(rgb_split[1]);
	color->b = ft_atoi(rgb_split[2]);
	free_split(rgb_split);
	if (!is_valid_rgb(color->r) || !is_valid_rgb(color->g)
		|| !is_valid_rgb(color->b))
		return (0);
	return (1);
}

void	take_color_values(t_color *color, char **line, int color_type,
		t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i >= 2 && line[i - 1] && line[i - 1][ft_strlen(line[i - 1])
		- 1] == '\n')
		line[i - 1][ft_strlen(line[i - 1]) - 1] = '\0';
	if (i != 2 || (color->r != -1))
	{
		print_error(INVALID_COLOR_LINE);
		return ;
	}
	if (!parse_rgb_values(line[1], color))
	{
		print_error(INVALID_RGB);
		return ;
	}
	map->colors_loaded |= (1 << color_type);
}
