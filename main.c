/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:13:39 by dogata            #+#    #+#             */
/*   Updated: 2021/01/25 00:18:37 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

int			main_loop(t_game *game)
{
	if (game->key_flag == true)
	{
		draw_floor_ceiling(game);
		raycast_calculation(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	}
	game->key_flag = false;
	return (0);
}

int			main(int argc, char **argv)
{
	t_game game;

	if (is_valid_command_line_argument(argc, argv, &game) == ERROR)
		exit(EXIT_FAILURE);
	information_display(&game);
	set_player_info(&game);
	set_color_info(&game);
	load_texture(&game);
	img_init(&game);
	if (game.save_flag == true)
	{
		draw_floor_ceiling(&game);
		raycast_calculation(&game);
		output_bmp(&game);
	}
	window_init(&game);
	mlx_hook(game.win, X_EVENT_WINDOW_CLOSE, 1L << 17, &close_window, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_FOCUS_IN, 1L << 21, &redraw, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	exit(EXIT_SUCCESS);
}
