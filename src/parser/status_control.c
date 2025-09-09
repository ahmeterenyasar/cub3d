/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igurses <igurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:39:36 by igurses           #+#    #+#             */
/*   Updated: 2025/09/09 16:03:110 by igurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void take_texture_path(char **path, char **line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    if(i == 3 || line[2][0] == '\n')
        free(line[i--]);
    if(i != 2 || *path)
        print_error(INVALID_TEXTURE_LINE); // free gelcek mi?
    *path = ft_strjoin(*path, line[1]);
    if (path[0][ft_strlen_for_map(*path)] == '\n')
        path[0][ft_strlen_for_map(*path)] = '\0';
    
}


int status_control(t_map *map, char *map_line)
{
    static int index = 0;

    while(index < 6)
    {
        if(map_line[0] == ' ' && !map_line[1])
            return 0;
        if(ft_strncmp(map_line, "NO", 2) == 0)
            take_texture_path(&map->img[0].path, ft_split(map_line, ' '));
        else if(ft_strncmp(map_line, "SO", 2) == 0)
            take_texture_path(&map->img[1].path, ft_split(map_line, ' '));
        else if(ft_strncmp(map_line, "WE", 2) == 0)
            take_texture_path(&map->img[2].path, ft_split(map_line, ' '));
        else if(ft_strncmp(map_line, "EA", 2) == 0)
            take_texture_path(&map->img[3].path, ft_split(map_line, ' '));
        // else if (ft_strncmp(map_line, "F", 1) == 0)
        // /*
        //     rgb
        // */
        // else if (ft_strncmp(map_line, "C", 1) == 0)
        // /*
        //     rgb
        // */
        else
            print_error(INVALID_FILE_VAR);
        index++;
        return(0);
    }
    // check_extantion(map_line);
    return(1);
}

