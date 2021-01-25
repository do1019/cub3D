/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:20:40 by dogata            #+#    #+#             */
/*   Updated: 2020/12/25 04:11:17 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*error_message_rt(int num)
{
	char *s1;
	char *s2;

	s1 = "The map does not have a player starting location";
	s2 = "The map does not closed by walls or has no floor";
	if (num == 1)
		return (s1);
	if (num == 2)
		return (s2);
	return (NULL);
}

static int	fill_location(char c)
{
	if (c == '0' || c == '-' || c == '2' ||
		c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	map_survey(int y, int x, t_game *game, int *result)
{
	if ((game->conf.map.copymap[y + 1][x] == 'X' ||
		game->conf.map.copymap[y][x + 1] == 'X' ||
		game->conf.map.copymap[y - 1][x] == 'X' ||
		game->conf.map.copymap[y][x - 1] == 'X' ||
		game->conf.map.copymap[y + 1][x] == '-' ||
		game->conf.map.copymap[y][x + 1] == '-' ||
		game->conf.map.copymap[y - 1][x] == '-' ||
		game->conf.map.copymap[y][x - 1] == '-' ||
		*result == ERROR))
	{
		*result = ERROR;
		return ;
	}
	game->conf.map.copymap[y][x] = 'F';
	if (fill_location((game)->conf.map.copymap[y + 1][x]))
		map_survey(y + 1, x, game, result);
	if (fill_location((game)->conf.map.copymap[y][x + 1]))
		map_survey(y, x + 1, game, result);
	if (fill_location((game)->conf.map.copymap[y - 1][x]))
		map_survey(y - 1, x, game, result);
	if (fill_location((game)->conf.map.copymap[y][x - 1]))
		map_survey(y, x - 1, game, result);
}

static void	map_copy(t_game *game, int diff)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < MAX_ROW - diff)
	{
		while (++j < MAX_COL - diff)
		{
			if (diff == 2)
				(game)->conf.map.map[i][j] =
					(game)->conf.map.readmap[i + 1][j + 1];
			else
				(game)->conf.map.copymap[i][j] = (game)->conf.map.readmap[i][j];
		}
		j = -1;
	}
}

int			is_valid_map(t_game *game)
{
	int x;
	int y;
	int result;

	if (game->conf.map.start_location_count > 1)
		return (putstr_error("The map has multiple player start locations"));
	if ((game)->conf.map.start_location_count == 0)
		return (putstr_error(error_message_rt(1)));
	x = (game)->pl.p_start_pos_x;
	y = (game)->pl.p_start_pos_y;
	map_copy(game, 0);
	result = SUCCESS;
	map_survey(y, x, game, &result);
	if (result == ERROR)
		return (putstr_error(error_message_rt(2)));
	map_copy(game, 2);
	return (SUCCESS);
}
