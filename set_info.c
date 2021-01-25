/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:59:39 by dogata            #+#    #+#             */
/*   Updated: 2021/01/23 10:39:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_game *game, double dir_x, double dir_y)
{
	game->pl.dir_x = dir_x;
	game->pl.dir_y = dir_y;
}

static void	set_plane(t_game *game, double plane_x, double plane_y)
{
	game->pl.plane_x = plane_x;
	game->pl.plane_y = plane_y;
}

void		set_player_info(t_game *game)
{
	game->pl.pos_x = game->pl.p_start_pos_y - 0.5;
	game->pl.pos_y = game->pl.p_start_pos_x - 0.5;
	if (game->pl.p_start_dir == 'N')
	{
		set_dir(game, -1.0, 0.0);
		set_plane(game, 0.0, 0.66);
	}
	else if (game->pl.p_start_dir == 'E')
	{
		set_dir(game, 0.0, 1.0);
		set_plane(game, 0.66, 0.0);
	}
	else if (game->pl.p_start_dir == 'S')
	{
		set_dir(game, 1.0, 0.0);
		set_plane(game, 0.0, -0.66);
	}
	else if (game->pl.p_start_dir == 'W')
	{
		set_dir(game, 0.0, -1.0);
		set_plane(game, -0.66, 0.0);
	}
}

int			set_color_info(t_game *game)
{
	game->conf.f_color = convert_rgb_to_int(game->conf.floor_color);
	game->conf.c_color = convert_rgb_to_int(game->conf.ceilling_color);
	if (game->conf.f_color == ERROR || game->conf.c_color == ERROR)
		exit(EXIT_FAILURE);
	return (0);
}
