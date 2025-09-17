/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/17 13:10:13 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = create_rgb_color(game->map->ceiling_color.r,
			game->map->ceiling_color.g, game->map->ceiling_color.b);
	floor_color = create_rgb_color(game->map->floor_color.r,
			game->map->floor_color.g, game->map->floor_color.b);
	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	draw_ceiling_and_floor(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
