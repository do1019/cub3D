/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:54:29 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 21:02:16 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_put_pixel(t_game *game)
{
	int i;
	int j;

	i = game->spr.draw_start_y;
	while (i < game->spr.draw_end_y)
	{
		j = i * 256 - game->conf.y_render_size * 128 +
			game->spr.sprite_height * 128;
		game->spr.spr_tex_y =
			((j * (double)TEX_HEIGHT) / game->spr.sprite_height) / 256;
		game->spr.color = game->tex.texture[4][TEX_WIDTH *
			game->spr.spr_tex_y + game->spr.spr_tex_x];
		if ((game->spr.color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(game, game->spr.stripe, i, game->spr.color);
		i++;
	}
}
