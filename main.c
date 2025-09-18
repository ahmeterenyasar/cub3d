/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:58:04 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:31:30 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	game;

	map = malloc(sizeof(t_map));
	if (!map)
		return (EXIT_FAILURE);
	init_data(map);
	if (!validate_arguments(argc, argv) || parser(argv, map) == -1
		|| init_graphics(&game, map) == -1)
	{
		free_map_data(map);
		free(map);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	cleanup_graphics(&game);
	return (EXIT_SUCCESS);
}
