/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:57:42 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 16:51:27 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	determine_texture_number(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_num = 3;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_num = 2;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_num = 1;
	else
		ray->tex_num = 0;
}

static void	calculate_texture_info(t_ray *ray, t_game *game)
{
	determine_texture_number(ray);
	calculate_wall_position(ray, game);
	calculate_texture_coordinates(ray, game);
}

static int	get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*dst;
	int		color;

	if (tex_x < 0 || tex_x >= game->textures[tex_num].width || tex_y < 0
		|| tex_y >= game->textures[tex_num].height)
		return (0);
	dst = game->textures[tex_num].addr + (tex_y
			* game->textures[tex_num].line_length + tex_x
			* (game->textures[tex_num].bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	tex_y;
	int	color;
	int	tex_height;

	tex_height = game->textures[ray->tex_num].height;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos % tex_height;
		ray->tex_pos += ray->step;
		color = get_texture_color(game, ray->tex_num, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = ((color >> 1) & 8355711);
		put_pixel(game, x, y, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray, game);
		perform_dda(&ray, game);
		calculate_wall_distance(&ray, game);
		calculate_texture_info(&ray, game);
		draw_wall_stripe(game, &ray, x);
		x++;
	}
}
