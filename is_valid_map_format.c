/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:20:28 by dogata            #+#    #+#             */
/*   Updated: 2020/12/25 04:09:22 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_player_location(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	set_player_location_info(t_game *game, char *row, int i)
{
	game->conf.map.readmap[game->conf.map.map_line + 1][i + 1] = row[i];
	game->pl.p_start_pos_x = i + 1;
	game->pl.p_start_pos_y = game->conf.map.map_line + 1;
	game->pl.p_start_dir = row[i];
	game->conf.map.start_location_count++;
}

static void	map_init(t_game *game)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	game->conf.map.map_initialized = true;
	while (i < MAX_ROW)
	{
		while (j < MAX_COL)
		{
			if (i == 0 || i == MAX_ROW - 1 || ((1 <= i && i <= MAX_ROW - 2)
				&& (j == 0 || j == (MAX_COL - 1))))
				k = 'X';
			else
				k = '-';
			game->conf.map.readmap[i][j] = k;
			j++;
		}
		j = 0;
		i++;
	}
}

static int	is_valid_map_row(char *row, t_game *game)
{
	int i;

	i = -1;
	while (row[++i])
	{
		if (row[i] == ' ')
			;
		else if (row[i] == '0')
			game->conf.map.readmap[game->conf.map.map_line + 1][i + 1] = '0';
		else if (row[i] == '1')
			game->conf.map.readmap[game->conf.map.map_line + 1][i + 1] = '1';
		else if (row[i] == '2')
		{
			game->conf.map.readmap[game->conf.map.map_line + 1][i + 1] = '2';
			ft_lstadd_back(&game->spr.head,
				ft_lstnew(spr_lstnew((double)(i + 0.5),
					(double)(game->conf.map.map_line + 0.5))));
			game->spr.sprite_count++;
		}
		else if (is_player_location(row[i]))
			set_player_location_info(game, row, i);
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int			is_valid_map_format(char *line, t_game *game)
{
	int		count;
	char	*s1;
	char	*s2;

	s1 = "Invalid configuration file format / The map is too large";
	s2 =
	"Invalid configuration file format / The map contains invalid character";
	count = (int)ft_strlen(line);
	if (game->conf.map.map_initialized == false)
		map_init(game);
	if (count > MAX_MAP)
		return (putstr_error(s1));
	if (game->conf.map.max_col < count)
		game->conf.map.max_col = count;
	game->conf.map.max_row++;
	if (game->conf.map.max_row > MAX_MAP)
		return (putstr_error(s1));
	if (is_valid_map_row(line, game) == ERROR)
		return (putstr_error(s2));
	game->conf.map.map_search_started = true;
	game->conf.map.map_line++;
	return (SUCCESS);
}
