/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:04:29 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 22:41:02 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ray_dir_delta_dist(t_game *game, int vertical_line_num)
{
	game->rc.camera_x =
		2 * vertical_line_num / (double)game->conf.x_render_size - 1;
	game->rc.ray_dir_x = game->pl.dir_x + game->pl.plane_x * game->rc.camera_x;
	game->rc.ray_dir_y = game->pl.dir_y + game->pl.plane_y * game->rc.camera_x;
	game->rc.map_x = (int)game->pl.pos_x;
	game->rc.map_y = (int)game->pl.pos_y;
	game->rc.delta_dist_x = fabs(1 / game->rc.ray_dir_x);
	game->rc.delta_dist_y = fabs(1 / game->rc.ray_dir_y);
}

static void	calc_step_side_dist(t_game *game)
{
	if (game->rc.ray_dir_x < 0)
	{
		game->rc.step_x = -1;
		game->rc.side_dist_x =
			(game->pl.pos_x - game->rc.map_x) * game->rc.delta_dist_x;
	}
	else
	{
		game->rc.step_x = 1;
		game->rc.side_dist_x =
			(game->rc.map_x + 1.0 - game->pl.pos_x) * game->rc.delta_dist_x;
	}
	if (game->rc.ray_dir_y < 0)
	{
		game->rc.step_y = -1;
		game->rc.side_dist_y =
			(game->pl.pos_y - game->rc.map_y) * game->rc.delta_dist_y;
	}
	else
	{
		game->rc.step_y = 1;
		game->rc.side_dist_y =
			(game->rc.map_y + 1.0 - game->pl.pos_y) * game->rc.delta_dist_y;
	}
}

static void	is_hit_wall(t_game *game)
{
	game->rc.hit = 0;
	while (game->rc.hit == 0)
	{
		if (game->rc.side_dist_x < game->rc.side_dist_y)
		{
			game->rc.side_dist_x += game->rc.delta_dist_x;
			game->rc.map_x += game->rc.step_x;
			game->rc.side = 0;
		}
		else
		{
			game->rc.side_dist_y += game->rc.delta_dist_y;
			game->rc.map_y += game->rc.step_y;
			game->rc.side = 1;
		}
		if (game->conf.map.map[game->rc.map_x][game->rc.map_y] == '1')
			game->rc.hit = 1;
	}
}

void		raycast_calculation(t_game *game)
{
	int vertical_line_num;

	vertical_line_num = 0;
	if (!(game->spr.buffer =
		ft_calloc(game->conf.x_render_size, sizeof(double))))
	{
		putstr_perror("");
		exit(EXIT_FAILURE);
	}
	while (vertical_line_num < game->conf.x_render_size)
	{
		calc_ray_dir_delta_dist(game, vertical_line_num);
		calc_step_side_dist(game);
		is_hit_wall(game);
		calc_draw_wall(game);
		calc_draw_texture(game);
		draw_wall_texture(game, vertical_line_num);
		game->spr.buffer[vertical_line_num] = game->rc.perp_wall_dist;
		vertical_line_num++;
	}
	if (game->spr.sprite_count > 0)
		calc_draw_sprite(game);
	free(game->spr.buffer);
}
