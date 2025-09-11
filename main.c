
#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map *map;
	
	map = malloc(sizeof(t_map));
	if (!map)
		return (EXIT_FAILURE);
	init_data(map);
	/* Validate arguments and file */
	if (!validate_arguments(argc, argv))
		return (EXIT_FAILURE);

	/* Parse the .cub file */
	parser(argv, map);

	
	/* TODO: Initialize graphics */
	/* TODO: Start game loop */
	
	/* Clean up memory */
	if (map->player)
		free(map->player);
	free(map);
	
	return (EXIT_SUCCESS);
}
