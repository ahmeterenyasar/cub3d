
#include "../../include/cub3d.h"

static void debug_print_all_data(t_map *map)
{
    printf("\n=== Parsed Data ===\n");
    printf("NO: %s\n", map->img[0].path ? map->img[0].path : "NULL");
    printf("SO: %s\n", map->img[1].path ? map->img[1].path : "NULL");
    printf("WE: %s\n", map->img[2].path ? map->img[2].path : "NULL");
    printf("EA: %s\n", map->img[3].path ? map->img[3].path : "NULL");
    printf("Floor RGB: %d,%d,%d\n", map->floor_color.r, map->floor_color.g, map->floor_color.b);
    printf("Ceiling RGB: %d,%d,%d\n", map->ceiling_color.r, map->ceiling_color.g, map->ceiling_color.b);
    printf("Player at: (%d, %d) facing %c\n", map->player->player_x, map->player->player_y, map->player->direction);
    printf("Map dimensions: %dx%d\n", map->map_width, map->map_height);
}

void find_width(char *line, t_map *map)
{
    static int max_width = 0;
    int len;
    
    len = ft_strlen(line);
    if (len > max_width)
        max_width = len;
    map->map_width = max_width;
}

int add_map_line(t_map *map, char ***map_copy, int *map_height)
{
    char **tmp;
    char *clean_line;
    int len;
    int i;

    map->map_is_ready = 1;
    tmp = malloc(sizeof(char *) * (*map_height + 1));
    if (!tmp)
        return (-1);
    
    for (i = 0; i < *map_height; i++)
        tmp[i] = (*map_copy)[i];
    
    clean_line = ft_strdup(map->map_line);
    len = ft_strlen(clean_line);
    if (len > 0 && (clean_line[len - 1] == '\n' || clean_line[len - 1] == '\r'))
        clean_line[len - 1] = '\0';
    if (len > 1 && (clean_line[len - 2] == '\r' || clean_line[len - 2] == '\n'))
        clean_line[len - 2] = '\0';
    
    tmp[*map_height] = clean_line;
    if (*map_copy)
        free(*map_copy);
    *map_copy = tmp;
    (*map_height)++;
    find_width(clean_line, map);
    
    return (0);
}

int read_map(int fd, t_map *map)
{
    int status;
    char **map_copy = NULL;
    int map_height = 0;

    while (1)
    {
        map->map_line = get_next_line(fd);
        if(!map->map_line)
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
    if (!validate_all_elements_loaded(map))
        return (-1);
    if (map->map_is_ready && process_map(map) == -1)
        return (-1);

    if (map->player->player_x == -1 && map->player->player_y == -1)
    {
        print_error(INVALID_MAP);
        return (-1);
    }
    close(fd);
    debug_print_all_data(map);
    return(0);
}
