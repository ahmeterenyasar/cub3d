
#include "../../include/cub3d.h"


int ft_strlen_for_map(char *map)
{
    int i;

    i = 0;
    while(map && map[i] && map[i] != '\n')
        i++;
    return (i);
}

void free_split(char **split)
{
    int i;
    
    if (!split)
        return;
    
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}