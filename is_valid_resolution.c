/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:54:50 by dogata            #+#    #+#             */
/*   Updated: 2021/01/24 04:34:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_valid_screen_size(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!(game->mlx = mlx_init()))
		return (putstr_perror(""));
	mlx_get_screen_size(game->mlx, &x, &y);
	if (game->conf.x_render_size > x)
		game->conf.x_render_size = x;
	if (game->conf.y_render_size > y)
		game->conf.y_render_size = y;
	return (0);
}

static int	is_valid_resolution(int i, char **tmp)
{
	int j;
	int k;

	k = 1;
	while (k < 3)
	{
		i = 0;
		j = ft_strlen(tmp[k]);
		while (ft_isdigit(tmp[k][i]))
			i++;
		if (j != i || i > 10 || tmp[k][0] == '0' ||
			(ft_atoll(tmp[k]) < 1 || INT_MAX < ft_atoll(tmp[k])))
			return (putstr_error("Invalid resolution"));
		k++;
	}
	return (SUCCESS);
}

int			is_valid_id_r(char *line, t_game *game)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(line, ' ');
	if (tmp == NULL || tmp[0] == NULL)
		return (free_dp_rt(&tmp, putstr_perror("")));
	while (tmp[i])
		i++;
	if (ft_memcmp(tmp[0], "R", 2) || i != 3)
		return (free_dp_rt(&tmp, putstr_error("Invalid identifier")));
	if (game->conf.id_r_flag == true)
		return (free_dp_rt(&tmp, putstr_error("Multiple R identifier")));
	if (is_valid_resolution(i, tmp) == ERROR)
		return (free_dp_rt(&tmp, ERROR));
	game->conf.x_render_size = ft_atoi(tmp[1]);
	game->conf.y_render_size = ft_atoi(tmp[2]);
	if (set_valid_screen_size(game) == ERROR)
		return ((free_dp_rt(&tmp, ERROR)));
	game->conf.id_r_flag = true;
	return (free_dp_rt(&tmp, SUCCESS));
}
