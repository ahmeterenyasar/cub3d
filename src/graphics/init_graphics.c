/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:40:12 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 17:17:10 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_and_win(t_game *game)
{
	if (!game->mlx)
	{
		print_error("Error\nFailed to initialize MLX");
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE);
	if (!game->win)
	{
		print_error("Error\nFailed to create window");
		cleanup_graphics(game);
		return (-1);
	}
	if (init_img_and_addr(game) == -1)
		return (-1);
	return (0);
}

int	init_img_and_addr(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		print_error("Error\nFailed to create image");
		cleanup_graphics(game);
		return (-1);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
	{
		print_error("Error\nFailed to get image data address");
		cleanup_graphics(game);
		return (-1);
	}
	return (0);
}

int	init_graphics(t_game *game, t_map *map)
{
	init_img(game, map);
	game->mlx = mlx_init();
	if (init_mlx_and_win(game) == -1)
		return (-1);
	if (load_textures(game) == -1)
	{
		print_error("Error\nFailed to load textures");
		cleanup_graphics(game);
		return (-1);
	}
	init_player_direction(game->map->player);
	mlx_hook(game->win, KEYPRESS, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, DESTROYNOTIFY, 1L << 17, handle_close, game);
	return (0);
}

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->map->player->dir_x + game->map->player->plane_x
		* ray->camera_x;
	ray->ray_dir_y = game->map->player->dir_y + game->map->player->plane_y
		* ray->camera_x;
	ray->map_x = (int)game->map->player->pos_x;
	ray->map_y = (int)game->map->player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}
