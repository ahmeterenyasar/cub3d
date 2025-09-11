#include "../../include/cub3d.h"

void take_texture_path(char **path, char **line, int texture_index, t_map *map)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    
    if(i >= 2 && line[i - 1] && line[i - 1][ft_strlen(line[i - 1]) - 1] == '\n')
        line[i - 1][ft_strlen(line[i - 1]) - 1] = '\0';
    
    if(i != 2 || *path)
    {
        print_error(INVALID_TEXTURE_LINE);
        return;
    }
    
    *path = ft_strdup(line[1]);
    map->textures_loaded |= (1 << texture_index);
}

int parse_rgb_values(char *rgb_string, t_color *color)
{
    char **rgb_split;
    int i;
    
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
    
    if (!is_valid_rgb(color->r) || !is_valid_rgb(color->g) || !is_valid_rgb(color->b))
        return (0);
    
    return (1);
}

void take_color_values(t_color *color, char **line, int color_type, t_map *map)
{
    int i;
    
    i = 0;
    while(line[i])
        i++;
    
    if(i >= 2 && line[i - 1] && line[i - 1][ft_strlen(line[i - 1]) - 1] == '\n')
        line[i - 1][ft_strlen(line[i - 1]) - 1] = '\0';
    
    if(i != 2 || (color->r != -1))
    {
        print_error(INVALID_COLOR_LINE);
        return;
    }
    
    if (!parse_rgb_values(line[1], color))
    {
        print_error(INVALID_RGB);
        return;
    }
    
    map->colors_loaded |= (1 << color_type);
}

int is_valid_rgb(int value)
{
    return (value >= 0 && value <= 255);
}

int skip_whitespace(char *line)
{
    int i = 0;
    
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'))
        i++;
    return (i);
}

int is_map_line(char *line)
{
    int i;
    
    if (!line)
        return (0);
    
    i = skip_whitespace(line);
    
    if (!line[i] || line[i] == '\n' || line[i] == '\r')
        return (0);
    
    while (line[i] && line[i] != '\n' && line[i] != '\r')
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
            line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int validate_all_elements_loaded(t_map *map)
{
    if (map->textures_loaded != 15)
    {
        print_error(MISSING_ELEMENT);
        return (0);
    }
    if (map->colors_loaded != 3)
    {
        print_error(MISSING_ELEMENT);
        return (0);
    }
    return (1);
}

int handle_empty_line(t_map *map, char *line)
{
    int i;
    
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

int handle_map_parsing(t_map *map, char *line)
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

int process_element_line(t_map *map, char **split)
{
    if (ft_strncmp(split[0], "NO", 2) == 0 && ft_strlen(split[0]) == 2)
        take_texture_path(&map->img[0].path, split, 0, map);
    else if (ft_strncmp(split[0], "SO", 2) == 0 && ft_strlen(split[0]) == 2)
        take_texture_path(&map->img[1].path, split, 1, map);
    else if (ft_strncmp(split[0], "WE", 2) == 0 && ft_strlen(split[0]) == 2)
        take_texture_path(&map->img[2].path, split, 2, map);
    else if (ft_strncmp(split[0], "EA", 2) == 0 && ft_strlen(split[0]) == 2)
        take_texture_path(&map->img[3].path, split, 3, map);
    else if (ft_strncmp(split[0], "F", 1) == 0 && ft_strlen(split[0]) == 1)
        take_color_values(&map->floor_color, split, 0, map);
    else if (ft_strncmp(split[0], "C", 1) == 0 && ft_strlen(split[0]) == 1)
        take_color_values(&map->ceiling_color, split, 1, map);
    else
    {
        print_error(INVALID_FILE_VAR);
        return (-1);
    }
    return (0);
}

int status_control(t_map *map, char *map_line)
{
    char **split;
    int empty_result;
    int map_result;
    
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
