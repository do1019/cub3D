/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:53:43 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 21:02:05 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = (char *)game->img.addr +
		(y * game->img.line_length + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceiling(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->conf.y_render_size)
	{
		x = 0;
		while (x < game->conf.x_render_size)
		{
			if (y < game->conf.y_render_size / 2)
				my_mlx_pixel_put(game, x, y, game->conf.c_color);
			else
				my_mlx_pixel_put(game, x, y, game->conf.f_color);
			x++;
		}
		y++;
	}
}

void	draw_wall_texture(t_game *game, int vertical_line_num)
{
	int y;

	y = game->rc.draw_start;
	while (y < game->rc.draw_end)
	{
		game->tex.tex_y = (int)game->tex.tex_pos & (TEX_HEIGHT - 1);
		game->tex.tex_pos += game->tex.step;
		if (game->rc.ray_dir_x < 0 && game->rc.side == 0)
			game->rc.color = game->tex.texture[game->tex.tex_num]
				[TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
		else if (game->rc.ray_dir_x > 0 && game->rc.side == 0)
			game->rc.color = game->tex.texture[game->tex.tex_num + 1]
				[TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
		else if (game->rc.ray_dir_y < 0 && game->rc.side == 1)
			game->rc.color = game->tex.texture[game->tex.tex_num + 2]
				[TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
		else
			game->rc.color = game->tex.texture[game->tex.tex_num + 3]
				[TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
		my_mlx_pixel_put(game, vertical_line_num, y, game->rc.color);
		y++;
	}
}

void	draw_sprite(t_game *game)
{
	game->spr.stripe = game->spr.draw_start_x;
	while (game->spr.stripe < game->spr.draw_end_x)
	{
		game->spr.spr_tex_x = (int)((256 * (game->spr.stripe -
			(-game->spr.sprite_width / 2 + game->spr.sprite_screen_x)) *
				(double)TEX_WIDTH / game->spr.sprite_width) / 256);
		if (game->spr.transform_y > 0 && game->spr.stripe > 0 &&
			game->spr.stripe < game->conf.x_render_size &&
				game->spr.transform_y < game->spr.buffer[game->spr.stripe])
			draw_sprite_put_pixel(game);
		game->spr.stripe++;
	}
}

int		redraw(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
