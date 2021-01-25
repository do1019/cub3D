/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 03:17:06 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 16:54:38 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	window_init(t_game *game)
{
	game->win = mlx_new_window(game->mlx,
		game->conf.x_render_size, game->conf.y_render_size, "cub3D");
}

void	img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx,
		game->conf.x_render_size, game->conf.y_render_size);
	game->img.addr = (int *)mlx_get_data_addr(game->img.img,
		&game->img.bpp, &game->img.line_length, &game->img.endian);
}
