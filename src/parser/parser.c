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
    int status;
    int map_started = 0;

    while (1)
    {
        map->map_line = get_next_line(fd);
        if(!map->map_line)
            break ;
        
        status = status_control(map, map->map_line);
        
        // map line detected
        if (status == 1) 
        {
            map_started = 1;
            if (add_map_line(map, map->map_line) == -1)
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
    
    if (!validate_all_elements_loaded(map))
        return (-1);
    
    if (map_started && process_map(map) == -1)
        return (-1);
    
    return (0);
}

int parser(char **argv, t_map *map)
{
    int fd = open(argv[1], O_RDONLY);
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
    
    close(fd);
    
    // Print parsed data
    printf("\n=== Parsed Data ===\n");
    printf("NO: %s\n", map->img[0].path ? map->img[0].path : "NULL");
    printf("SO: %s\n", map->img[1].path ? map->img[1].path : "NULL");
    printf("WE: %s\n", map->img[2].path ? map->img[2].path : "NULL");
    printf("EA: %s\n", map->img[3].path ? map->img[3].path : "NULL");
    printf("Floor RGB: %d,%d,%d\n", map->floor_color.r, map->floor_color.g, map->floor_color.b);
    printf("Ceiling RGB: %d,%d,%d\n", map->ceiling_color.r, map->ceiling_color.g, map->ceiling_color.b);
    printf("Player at: (%d, %d) facing %c\n", map->player->player_x, map->player->player_y, map->player->direction);
    printf("Map dimensions: %dx%d\n", map->map_width, map->map_height);
    
    return(0);
}