/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igurses <igurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:09:12 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/15 15:01:48 by igurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_strlen_for_map(char *map)
{
	int	i;

	i = 0;
	while (map && map[i] && map[i] != '\n')
		i++;
	return (i);
}

int	is_valid_rgb(int value)
{
	return (value >= 0 && value <= 255);
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'))
		i++;
	return (i);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

void remove_eof(char *line)
{
    int len;
    
    if (!line)
        return;
    len = ft_strlen(line);
    if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        line[len - 1] = '\0';
    len = ft_strlen(line);
    if (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n'))
        line[len - 1] = '\0';
}
