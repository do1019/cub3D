/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:47:08 by dogata            #+#    #+#             */
/*   Updated: 2020/12/23 21:56:30 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pressed_arrow_left(t_game *game)
{
	if (game->conf.map.map[(int)(game->pl.pos_x - game->pl.dir_y *
		MOVESPEED)][(int)(game->pl.pos_y)] != '1' && (game)->conf.map.map
			[(int)(game->pl.pos_x - game->pl.dir_y * MOVESPEED)]
				[(int)(game->pl.pos_y)] != '2')
		game->pl.pos_x -= game->pl.dir_y * (MOVESPEED + 0.00001);
	if (game->conf.map.map[(int)(game->pl.pos_x)][(int)(game->pl.pos_y +
		game->pl.dir_x * MOVESPEED)] != '1' && game->conf.map.map
			[(int)(game->pl.pos_x)][(int)(game->pl.pos_y + game->pl.dir_x *
				MOVESPEED)] != '2')
		(game)->pl.pos_y += (game)->pl.dir_x * (MOVESPEED + 0.00001);
}

static void	pressed_arrow_right(t_game *game)
{
	if (game->conf.map.map[(int)(game->pl.pos_x + game->pl.dir_y *
		MOVESPEED)][(int)(game->pl.pos_y)] != '1' && game->conf.map.map
			[(int)(game->pl.pos_x + game->pl.dir_y * MOVESPEED)]
				[(int)(game->pl.pos_y)] != '2')
		game->pl.pos_x += game->pl.dir_y * (MOVESPEED + 0.00001);
	if (game->conf.map.map[(int)(game->pl.pos_x)][(int)(game->pl.pos_y -
		game->pl.dir_x * MOVESPEED)] != '1' && game->conf.map.map
			[(int)(game->pl.pos_x)][(int)(game->pl.pos_y - game->pl.dir_x *
				MOVESPEED)] != '2')
		game->pl.pos_y -= game->pl.dir_x * (MOVESPEED + 0.00001);
}

int			deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (key_code == KEY_W || key_code == ARROW_KEY_UP)
		pressed_w_up(game);
	else if (key_code == KEY_S || key_code == ARROW_KEY_DOWN)
		pressed_s_down(game);
	else if (key_code == KEY_A)
		pressed_a(game);
	else if (key_code == KEY_D)
		pressed_d(game);
	else if (key_code == ARROW_KEY_L)
		pressed_arrow_left(game);
	else if (key_code == ARROW_KEY_R)
		pressed_arrow_right(game);
	game->key_flag = true;
	return (0);
}
