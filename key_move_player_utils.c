/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move_player_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:47:00 by dogata            #+#    #+#             */
/*   Updated: 2020/12/23 21:57:25 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pressed_w_up(t_game *game)
{
	if (game->conf.map.map[(int)(game->pl.pos_x + game->pl.dir_x * MOVESPEED)]
		[(int)(game->pl.pos_y)] != '1' &&
			game->conf.map.map[(int)(game->pl.pos_x + game->pl.dir_x *
				MOVESPEED)][(int)(game->pl.pos_y)] != '2')
		(game)->pl.pos_x += (game)->pl.dir_x * (MOVESPEED + 0.00001);
	if (game->conf.map.map[(int)(game->pl.pos_x)][(int)(game->pl.pos_y +
		game->pl.dir_y * MOVESPEED)] != '1' && game->conf.map.map
			[(int)(game->pl.pos_x)][(int)(game->pl.pos_y + game->pl.dir_y *
				MOVESPEED)] != '2')
		game->pl.pos_y += game->pl.dir_y * (MOVESPEED + 0.00001);
}

void	pressed_s_down(t_game *game)
{
	if (game->conf.map.map[(int)(game->pl.pos_x - game->pl.dir_x * MOVESPEED)]
		[(int)(game->pl.pos_y)] != '1' &&
			game->conf.map.map[(int)(game->pl.pos_x - game->pl.dir_x *
				MOVESPEED)][(int)(game->pl.pos_y)] != '2')
		game->pl.pos_x -= game->pl.dir_x * (MOVESPEED + 0.00001);
	if (game->conf.map.map[(int)(game->pl.pos_x)][(int)(game->pl.pos_y -
		game->pl.dir_y * MOVESPEED)] != '1' && game->conf.map.map
			[(int)(game->pl.pos_x)][(int)(game->pl.pos_y - game->pl.dir_y *
				MOVESPEED)] != '2')
		game->pl.pos_y -= game->pl.dir_y * (MOVESPEED + 0.00001);
}

void	pressed_a(t_game *game)
{
	game->pl.old_dir_x = game->pl.dir_x;
	game->pl.dir_x =
		game->pl.dir_x * cos(ROTSPEED) - game->pl.dir_y * sin(ROTSPEED);
	game->pl.dir_y =
		game->pl.old_dir_x * sin(ROTSPEED) + game->pl.dir_y * cos(ROTSPEED);
	game->pl.old_plane_x = game->pl.plane_x;
	game->pl.plane_x =
		game->pl.plane_x * cos(ROTSPEED) - game->pl.plane_y * sin(ROTSPEED);
	game->pl.plane_y =
		game->pl.old_plane_x * sin(ROTSPEED) + game->pl.plane_y * cos(ROTSPEED);
}

void	pressed_d(t_game *game)
{
	game->pl.old_dir_x = game->pl.dir_x;
	game->pl.dir_x =
		game->pl.dir_x * cos(-ROTSPEED) - game->pl.dir_y * sin(-ROTSPEED);
	game->pl.dir_y =
		game->pl.old_dir_x * sin(-ROTSPEED) + game->pl.dir_y * cos(-ROTSPEED);
	game->pl.old_plane_x = game->pl.plane_x;
	game->pl.plane_x =
		game->pl.plane_x * cos(-ROTSPEED) - game->pl.plane_y * sin(-ROTSPEED);
	game->pl.plane_y =
		game->pl.old_plane_x * sin(-ROTSPEED) +
			game->pl.plane_y * cos(-ROTSPEED);
}
