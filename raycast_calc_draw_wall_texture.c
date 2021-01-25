/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_draw_wall_texture.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:17:59 by dogata            #+#    #+#             */
/*   Updated: 2020/12/26 08:02:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_draw_wall(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.perp_wall_dist = (game->rc.map_x -
			game->pl.pos_x + (1 - game->rc.step_x) / 2) / game->rc.ray_dir_x;
	else
		game->rc.perp_wall_dist = (game->rc.map_y -
			game->pl.pos_y + (1 - game->rc.step_y) / 2) / game->rc.ray_dir_y;
	game->rc.line_height =
		(int)(game->conf.y_render_size / game->rc.perp_wall_dist);
	game->rc.draw_start =
		(game->rc.line_height * -1) / 2 + game->conf.y_render_size / 2;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = game->rc.line_height / 2 + game->conf.y_render_size / 2;
	if (game->rc.draw_end >= game->conf.y_render_size)
		game->rc.draw_end = game->conf.y_render_size - 1;
}

void	calc_draw_texture(t_game *game)
{
	game->tex.tex_num = game->conf.map.map[game->rc.map_x][game->rc.map_y] - 49;
	if (game->rc.side == 0)
		game->tex.wall_x =
			game->pl.pos_y + game->rc.perp_wall_dist * game->rc.ray_dir_y;
	else
		game->tex.wall_x =
			game->pl.pos_x + game->rc.perp_wall_dist * game->rc.ray_dir_x;
	game->tex.wall_x -= floor(game->tex.wall_x);
	game->tex.tex_x = (int)(game->tex.wall_x * (double)TEX_WIDTH);
	if (game->rc.side == 0 && game->rc.ray_dir_x > 0)
		game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
	if (game->rc.side == 1 && game->rc.ray_dir_y < 0)
		game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
	game->tex.step = 1.0 * (double)TEX_HEIGHT / (game)->rc.line_height;
	game->tex.tex_pos =
		(game->rc.draw_start - game->conf.y_render_size / 2 +
			game->rc.line_height / 2) * game->tex.step;
}
