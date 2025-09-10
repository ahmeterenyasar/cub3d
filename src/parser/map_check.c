/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:55:28 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 17:59:45 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int add_map_line(t_map *map, char *line)
{
    char **new_map;
    int i;
    int len;
    
    // Remove newline and carriage return if exists
    len = ft_strlen(line);
    if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        line[len - 1] = '\0';
    if (len > 1 && (line[len - 2] == '\r' || line[len - 2] == '\n'))
        line[len - 2] = '\0';
    
    // Skip empty lines
    if (ft_strlen(line) == 0)
        return (0);
    
    // Allocate new map array
    new_map = malloc(sizeof(char *) * (map->map_height + 2));
    if (!new_map)
        return (-1);
    
    // Copy existing lines
    i = 0;
    while (i < map->map_height)
    {
        new_map[i] = map->map_copy[i];
        i++;
    }
    
    // Add new line
    new_map[map->map_height] = ft_strdup(line);
    if (!new_map[map->map_height])
    {
        free(new_map);
        return (-1);
    }
    
    new_map[map->map_height + 1] = NULL;
    
    // Free old array (not the strings)
    if (map->map_copy)
        free(map->map_copy);
    
    map->map_copy = new_map;
    map->map_height++;
    
    return (0);
}

int calculate_map_dimensions(t_map *map)
{
    int i;
    int current_width;
    
    map->map_width = 0;
    i = 0;
    while (i < map->map_height)
    {
        current_width = ft_strlen(map->map_copy[i]);
        if (current_width > map->map_width)
            map->map_width = current_width;
        i++;
    }
    return (0);
}

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int find_player(t_map *map)
{
    int x;
    int y;
    int player_count = 0;
    
    y = 0;
    while (y < map->map_height)
    {
        x = 0;
        while (x < (int)ft_strlen(map->map_copy[y]))
        {
            if (!is_valid_map_char(map->map_copy[y][x]))
            {
                print_error(INVALID_MAP);
                return (-1);
            }
            
            if (map->map_copy[y][x] == 'N' || map->map_copy[y][x] == 'S' || 
                map->map_copy[y][x] == 'E' || map->map_copy[y][x] == 'W')
            {
                player_count++;
                if (player_count > 1)
                {
                    print_error(DUPLICATE_PLAYER);
                    return (-1);
                }
                map->player->player_x = x;
                map->player->player_y = y;
                map->player->direction = map->map_copy[y][x];
                
                // Replace player position with empty space for flood fill
                map->map_copy[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    
    if (player_count == 0)
    {
        print_error(NO_PLAYER);
        return (-1);
    }
    
    return (0);
}

char **create_visited_array(t_map *map)
{
    char **visited;
    int i;
    int j;
    
    visited = malloc(sizeof(char *) * map->map_height);
    if (!visited)
        return (NULL);
    
    i = 0;
    while (i < map->map_height)
    {
        visited[i] = malloc(sizeof(char) * (map->map_width + 1));
        if (!visited[i])
        {
            while (--i >= 0)
                free(visited[i]);
            free(visited);
            return (NULL);
        }
        
        j = 0;
        while (j < map->map_width)
        {
            visited[i][j] = '0';
            j++;
        }
        visited[i][j] = '\0';
        i++;
    }
    
    return (visited);
}

void free_visited_array(char **visited, int height)
{
    int i;
    
    if (!visited)
        return;
    
    i = 0;
    while (i < height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
}

int flood_fill(t_map *map, int x, int y, char **visited)
{
    // Check bounds
    if (y < 0 || y >= map->map_height || x < 0)
        return (-1);
    
    // Check if we're going out of the actual line length
    if (x >= (int)ft_strlen(map->map_copy[y]))
    {
        // Going beyond line means hitting void/edge - invalid
        return (-1);
    }
    
    // If already visited
    if (visited[y][x] == '1')
        return (0);
    
    char current_char = map->map_copy[y][x];
    
    // If wall
    if (current_char == '1')
        return (0);
    
    // If we encounter a space, it's invalid in reachable areas
    if (current_char == ' ')
        return (-1);
    
    // If empty space (walkable area)
    if (current_char == '0')
    {
        // Check if we're at any edge of the map grid
        if (x == 0 || y == 0 || y == map->map_height - 1)
            return (-1);
        
        // Check if we're at the end of this line
        if (x == (int)ft_strlen(map->map_copy[y]) - 1)
            return (-1);
        
        // Check if adjacent positions would be out of bounds or different line lengths
        // This handles irregular map shapes
        if (y > 0 && x >= (int)ft_strlen(map->map_copy[y - 1]))
            return (-1);
        if (y < map->map_height - 1 && x >= (int)ft_strlen(map->map_copy[y + 1]))
            return (-1);
        
        // Mark as visited
        visited[y][x] = '1';
        
        // Continue flood fill in all directions
        if (flood_fill(map, x + 1, y, visited) == -1)
            return (-1);
        if (flood_fill(map, x - 1, y, visited) == -1)
            return (-1);
        if (flood_fill(map, x, y + 1, visited) == -1)
            return (-1);
        if (flood_fill(map, x, y - 1, visited) == -1)
            return (-1);
    }
    
    return (0);
}

int validate_map_walls(t_map *map)
{
    char **visited;
    int result;
    
    visited = create_visited_array(map);
    if (!visited)
        return (-1);
    
    result = flood_fill(map, map->player->player_x, map->player->player_y, visited);
    
    free_visited_array(visited, map->map_height);
    
    if (result == -1)
    {
        print_error(UNCLOSED_MAP);
        return (-1);
    }
    
    return (0);
}

int process_map(t_map *map)
{
    if (map->map_height == 0)
    {
        print_error(INVALID_MAP);
        return (-1);
    }
    calculate_map_dimensions(map);
    if (find_player(map) == -1)
        return (-1);
    if (validate_map_walls(map) == -1)
        return (-1);

    return (0);
}
