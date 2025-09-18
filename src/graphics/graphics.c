/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 14:42:13 by ayasar           ###   ########.fr       */
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

int	fail_for_img(t_game *game, int i, int j)
{
	if (!game->textures[i].img)
	{
		j = 0;
		while (j < i)
		{
			if (game->textures[j].img)
				mlx_destroy_image(game->mlx, game->textures[j].img);
			j++;
		}
		return (-1);
	}
	return (0);
}

int	fail_for_addr(t_game *game, int i, int j)
{
	if (!game->textures[i].addr)
	{
		mlx_destroy_image(game->mlx, game->textures[i].img);
		j = 0;
		while (j < i)
		{
			if (game->textures[j].img)
				mlx_destroy_image(game->mlx, game->textures[j].img);
			j++;
		}
		return (-1);
	}
	return (0);
}

int	load_textures(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 4)
	{
		if (game->map->img[i].path)
		{
			game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
					game->map->img[i].path, &game->textures[i].width,
					&game->textures[i].height);
			if (fail_for_img(game, i, j) == -1)
				return (-1);
			game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
					&game->textures[i].bits_per_pixel,
					&game->textures[i].line_length, &game->textures[i].endian);
			if (fail_for_addr(game, i, j) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

void	cleanup_graphics(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
