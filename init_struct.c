/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 03:15:41 by dogata            #+#    #+#             */
/*   Updated: 2020/12/25 04:09:29 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_struct_init(t_game *game)
{
	game->conf.x_render_size = 0;
	game->conf.y_render_size = 0;
	game->conf.map.map_initialized = false;
	game->conf.map.map_search_started = false;
	game->conf.map.map_end = false;
	game->pl.p_start_pos_x = 0;
	game->pl.p_start_pos_y = 0;
	game->conf.map.start_location_count = 0;
	game->conf.map.max_row = 0;
	game->conf.map.max_col = 0;
	game->spr.sprite_count = 0;
	game->spr.head = NULL;
	game->key_flag = true;
	game->save_flag = false;
	game->conf.id_r_flag = false;
	game->conf.id_no_flag = false;
	game->conf.id_so_flag = false;
	game->conf.id_we_flag = false;
	game->conf.id_ea_flag = false;
	game->conf.id_s_flag = false;
	game->conf.id_f_flag = false;
	game->conf.id_c_flag = false;
	game->conf.map.map_line = 0;
}

void	bmp_struct_init(t_game *game)
{
	game->bmp.r_width =
		game->conf.x_render_size * 3 + game->conf.x_render_size % 4;
	game->bmp.file_size =
		game->conf.y_render_size * game->bmp.r_width + HEADER_SIZE;
	game->bmp.offset_to_data = HEADER_SIZE;
	game->bmp.info_header_size = INFO_HEADER_SIZE;
	game->bmp.planes = 1;
	game->bmp.color = 24;
	game->bmp.compress = 0;
	game->bmp.data_size = game->conf.y_render_size * game->bmp.r_width;
	game->bmp.xppm = 1;
	game->bmp.yppm = 1;
	ft_bzero(game->bmp.header_buf, HEADER_SIZE);
	ft_memcpy(game->bmp.header_buf, "BM", 2);
	ft_memcpy(game->bmp.header_buf + 2, &game->bmp.file_size, 4);
	ft_memcpy(game->bmp.header_buf + 10, &game->bmp.offset_to_data, 4);
	ft_memcpy(game->bmp.header_buf + 14, &game->bmp.info_header_size, 4);
	ft_memcpy(game->bmp.header_buf + 18, &game->conf.x_render_size, 4);
	ft_memcpy(game->bmp.header_buf + 22, &game->conf.y_render_size, 4);
	ft_memcpy(game->bmp.header_buf + 26, &game->bmp.planes, 4);
	ft_memcpy(game->bmp.header_buf + 28, &game->bmp.color, 4);
	ft_memcpy(game->bmp.header_buf + 30, &game->bmp.compress, 4);
	ft_memcpy(game->bmp.header_buf + 34, &game->bmp.data_size, 4);
	ft_memcpy(game->bmp.header_buf + 38, &game->bmp.xppm, 4);
	ft_memcpy(game->bmp.header_buf + 42, &game->bmp.yppm, 4);
}
