/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:57:42 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 15:12:53 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
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

static void	calculate_step_and_side_dist(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->map->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->map->player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->map->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->map->player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map_copy[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->map->player->pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->map->player->pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

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

static void	calculate_wall_position(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->map->player->pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = game->map->player->pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static void	calculate_texture_coordinates(t_ray *ray, t_game *game)
{
	int	tex_width;

	tex_width = game->textures[ray->tex_num].width;
	ray->tex_x = (int)(ray->wall_x * (double)tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
	ray->step = 1.0 * game->textures[ray->tex_num].height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
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
		// Make y-side walls (horizontal walls) darker for depth effect
		if (ray->side == 1)
			color = ((color >> 1) & 8355711);
		// Darken by shifting RGB and masking
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
