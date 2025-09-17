
#include "include/cub3d.h"
#include "include/graphics.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	game;
	
	map = malloc(sizeof(t_map));
	if (!map)
		return (EXIT_FAILURE);
	init_data(map);
	if (!validate_arguments(argc, argv))
	{
		free_map_data(map);
		free(map);
		return (EXIT_FAILURE);
	}
	if (parser(argv, map) == -1)
	{
		free_map_data(map);
		free(map);
		return (EXIT_FAILURE);
	}
	debug_print_all_data(map);
	print_map_copy(map->map_copy, map->map_height);
	/* Initialize graphics */
	if (init_graphics(&game, map) == -1)
	{
		print_error("Error\nFailed to initialize graphics");
		free_map_data(map);
		free(map);
		return (EXIT_FAILURE);
	}
	/* Start game loop */
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	/* Clean up memory */
	cleanup_graphics(&game);
	free_map_data(map);
	free(map);
	return (EXIT_SUCCESS);
}
