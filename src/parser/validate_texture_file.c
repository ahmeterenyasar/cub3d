/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:08:29 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 17:17:11 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_texture_extension(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

int	is_texture_accessible(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	validate_texture_file(char *path)
{
	if (!is_valid_texture_extension(path))
	{
		print_error(INVALID_TEXTURE_LINE);
		return (0);
	}
	if (!is_texture_accessible(path))
	{
		print_error(ERR_FILE_OPEN);
		return (0);
	}
	return (1);
}

int	take_texture_path(char **path, char **line, int texture_index, t_map *map)
{
	char	*trimmed_line;
	int		len;

	if (!line[1] || *path)
	{
		print_error(INVALID_TEXTURE_LINE);
		return (-1);
	}
	trimmed_line = line[1];
	len = ft_strlen(trimmed_line);
	if (len > 0 && trimmed_line[len - 1] == '\n')
		trimmed_line[len - 1] = '\0';
	if (!validate_texture_file(trimmed_line))
		return (-1);
	*path = ft_strdup(trimmed_line);
	map->textures_loaded |= (1 << texture_index);
	return (0);
}
