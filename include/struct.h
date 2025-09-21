/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:50:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/21 17:37:07 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	char		*path;
}				t_img;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		direction;
	int			player_count;
	int			player_x;
	int			player_y;
}				t_player;

typedef struct s_map
{
	char		**map_copy;
	char		*map_line;
	int			map_height;
	int			map_width;
	char		*clean_line;
	int			map_started;
	int			map_is_ready;
	t_player	*player;
	t_img		img[4];
	t_color		floor_color;
	t_color		ceiling_color;
	int			textures_loaded;
	int			colors_loaded;
}				t_map;

#endif