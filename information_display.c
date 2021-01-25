/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:54:17 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 15:07:45 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_resolution(t_game *game)
{
	char *resolution_x;
	char *resolution_y;

	resolution_x = ft_itoa(game->conf.x_render_size);
	resolution_y = ft_itoa(game->conf.y_render_size);
	if (!resolution_x || !resolution_y)
	{
		putstr_perror("");
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd("\n-----------Resolution------------", 1);
	ft_putstr_fd("R ", 1);
	ft_putstr_fd(resolution_x, 1);
	free_sp_rt(&resolution_x, 0);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(resolution_y, 1);
	free_sp_rt(&resolution_y, 0);
	ft_putstr_fd("\n", 1);
}

static void	display_textures(t_game *game)
{
	int i;

	i = -1;
	ft_putendl_fd("------------Textures-------------", 1);
	while (++i < TEX_NUM)
	{
		if (i == 0)
			ft_putstr_fd("NO ", 1);
		if (i == 1)
			ft_putstr_fd("SO ", 1);
		if (i == 2)
			ft_putstr_fd("WE ", 1);
		if (i == 3)
			ft_putstr_fd("EA ", 1);
		if (i == 4)
			ft_putstr_fd("S  ", 1);
		ft_putendl_fd(game->conf.texture_path[i], 1);
	}
}

static void	display_colors(t_game *game)
{
	int	i;

	i = -1;
	ft_putendl_fd("--------------Color--------------", 1);
	while (++i < 2)
	{
		if (i == 0)
			display_f_color(game);
		if (i == 1)
			display_c_color(game);
		ft_putchar_fd('\n', 1);
	}
}

static void	display_map(t_game *game)
{
	int i;
	int j;

	i = -1;
	ft_putendl_fd("---------------Map---------------", 1);
	while (++i < game->conf.map.max_row)
	{
		j = -1;
		while (++j < game->conf.map.max_col)
			ft_putchar_fd(game->conf.map.map[i][j], 1);
		ft_putchar_fd('\n', 1);
	}
	ft_putendl_fd("---------------------------------", 1);
}

void		information_display(t_game *game)
{
	display_resolution(game);
	display_textures(game);
	display_colors(game);
	display_map(game);
	ft_putendl_fd("\n\x1b[32mConfiguration file read successfully.\x1b[m\n", 1);
}
