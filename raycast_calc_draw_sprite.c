/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_draw_sprite.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:21:29 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 21:31:26 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_current_sprite
	(t_game *game, t_list **current_lst, t_sprlst **current_spr)
{
	*current_lst = game->spr.head;
	*current_spr = (*current_lst)->content;
}

void
	calc_sprite_distance
	(t_game *game, t_list **current_lst, t_sprlst **current_spr)
{
	int i;

	i = -1;
	while (++i < game->spr.sprite_count)
	{
		(*current_spr)->distance =
			((game->pl.pos_x - (*current_spr)->y) *
				(game->pl.pos_x - (*current_spr)->y) +
					(game->pl.pos_y - (*current_spr)->x) *
						(game->pl.pos_y - (*current_spr)->x));
		*current_lst = (*current_lst)->next;
		if (*current_lst == NULL)
			break ;
		*current_spr = (*current_lst)->content;
	}
}

void
	calc_sprite_pos_size(t_game *game, t_sprlst **current_spr)
{
	game->spr.sprite_x = (*current_spr)->y - game->pl.pos_x;
	game->spr.sprite_y = (*current_spr)->x - game->pl.pos_y;
	game->spr.inv_det = 1.0 /
		(game->pl.plane_x * game->pl.dir_y - game->pl.dir_x * game->pl.plane_y);
	game->spr.transform_x =
		game->spr.inv_det * (game->pl.dir_y *
			game->spr.sprite_x - game->pl.dir_x * game->spr.sprite_y);
	game->spr.transform_y =
		game->spr.inv_det * (-game->pl.plane_y *
			game->spr.sprite_x + game->pl.plane_x * game->spr.sprite_y);
	game->spr.sprite_screen_x =
		(int)((game->conf.x_render_size / 2) *
			(1 + game->spr.transform_x / game->spr.transform_y));
	game->spr.sprite_height =
		(long)fabs(game->conf.y_render_size / game->spr.transform_y);
}

void
	calc_sprite_draw_pixel_height_width(t_game *game)
{
	game->spr.draw_start_y =
		-game->spr.sprite_height / 2 + game->conf.y_render_size / 2;
	if (game->spr.draw_start_y < 0)
		game->spr.draw_start_y = 0;
	game->spr.draw_end_y =
		game->spr.sprite_height / 2 + game->conf.y_render_size / 2;
	if (game->spr.draw_end_y >= game->conf.y_render_size)
		game->spr.draw_end_y = game->conf.y_render_size - 1;
	game->spr.sprite_width =
		(long)fabs((game->conf.y_render_size / game->spr.transform_y));
	game->spr.draw_start_x =
		(long)(-game->spr.sprite_width / 2 + game->spr.sprite_screen_x);
	if (game->spr.draw_start_x < 0)
		game->spr.draw_start_x = 0;
	game->spr.draw_end_x =
		(long)(game->spr.sprite_width / 2 + game->spr.sprite_screen_x);
	if (game->spr.draw_end_x >= game->conf.x_render_size)
		game->spr.draw_end_x = game->conf.x_render_size - 1;
}

void
	calc_draw_sprite(t_game *game)
{
	int			i;
	t_list		*current_lst;
	t_sprlst	*current_spr;

	i = -1;
	update_current_sprite(game, &current_lst, &current_spr);
	calc_sprite_distance(game, &current_lst, &current_spr);
	sort_sprites(game);
	update_current_sprite(game, &current_lst, &current_spr);
	while (++i < game->spr.sprite_count)
	{
		calc_sprite_pos_size(game, &current_spr);
		calc_sprite_draw_pixel_height_width(game);
		draw_sprite(game);
		current_lst = current_lst->next;
		if (current_lst == NULL)
			break ;
		current_spr = current_lst->content;
	}
}
