/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:49:24 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 17:59:44 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

int read_map(int fd, t_map *map)
{

    while (1)
    {
        map->map_line = get_next_line(fd);
        // printf("%s", map->map_line);
        if(!map->map_line)
            break ;
        status_control(map, map->map_line);
        // if(status_control(map, map.map_line) == 1)
        // {
        //     //
        // }
        // free(map.map_line);
    }
    return 0;
}

int parser(char **argv, t_map *map)
{
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        print_error(ERR_FILE_OPEN);
        return (-1);
    }
    read_map(fd, map);
    // if(!is_valid_map(map))
    // {
    //     //error check_map_is_valid -> duvarlara bakcak 
    // }
    close(fd);
    return(0);
}