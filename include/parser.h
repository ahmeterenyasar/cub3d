/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:50:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 16:11:332 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_img
{
	char		*path;
}				t_img;

// unused
typedef struct s_cam
{
	int plane_x; // 0
	int plane_y; // 0.66 -> 66 derece FOV
}				t_cam;

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
	int player_x; // Grid coordinates for parsing
	int player_y; // Grid coordinates for parsing
}				t_player;

typedef struct s_map
{
	char		**map_copy;
	char		*map_line;
	int			map_height;
	int			map_width;
	char		*clean_line;
	int 		map_started; // Flag to track if map parsing has begun
	int			map_is_ready;
	t_player	*player;
	t_img img[4]; // NO, SO, WE, EA
	t_color		floor_color;
	t_color		ceiling_color;
	int textures_loaded; // bitmask for loaded textures
	int colors_loaded;   // bitmask for loaded colors
}				t_map;

#endif