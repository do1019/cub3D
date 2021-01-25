/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:33:22 by dogata            #+#    #+#             */
/*   Updated: 2021/01/25 00:29:40 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_comma_num(char **tmp)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (tmp[1][++i])
	{
		if (tmp[1][i] == ',')
			j++;
		if (j > 2)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	is_valid_color_format(t_game *game, char **tmp)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	if (ft_strlen(tmp[0]) != 1 ||
		(ft_memcmp(tmp[0], "F", 2) && ft_memcmp(tmp[0], "C", 2)) ||
			i != 2 || is_valid_comma_num(tmp) == ERROR)
		return (putstr_error("Invalid identifier / configuration file format"));
	if (!ft_memcmp(tmp[0], "F", 2) && game->conf.id_f_flag == true)
		return (putstr_error("Multiple F identifier"));
	if (!ft_memcmp(tmp[0], "C", 2) && game->conf.id_c_flag == true)
		return (putstr_error("Multiple C identifier"));
	return (0);
}

static int	is_valid_rgb_code(char **tmp)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		if (ft_strlen(tmp[i]) == 0 || ft_strlen(tmp[i]) > 3)
			return (ERROR);
		while (ft_isdigit(tmp[i][j]))
			j++;
		if (ft_strlen(tmp[i]) != j || (j > 1 && tmp[i][0] == '0') ||
		255 < ft_atoi(tmp[i]) || 0 > ft_atoi(tmp[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	is_valid_id_color(t_game *game, char **tmp, char *id)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (putstr_error("Invalid color format"));
	if (is_valid_rgb_code(tmp) == ERROR)
		return (putstr_error("Invalid RGB code"));
	i = -1;
	if (id[0] == 'F')
		while (++i < 3)
			(game)->conf.floor_color[i] = ft_atoi(tmp[i]);
	if (id[0] == 'C')
		while (++i < 3)
			(game)->conf.ceilling_color[i] = ft_atoi(tmp[i]);
	if (id[0] == 'F')
		game->conf.id_f_flag = true;
	if (id[0] == 'C')
		game->conf.id_c_flag = true;
	return (SUCCESS);
}

int			is_valid_id_colors(char *line, t_game *game)
{
	char	**tmp;
	char	*tmp2;
	char	*id;

	tmp = ft_split(line, ' ');
	if (tmp == NULL || tmp[0] == NULL)
		return (free_dp_rt(&tmp, putstr_perror("")));
	if (is_valid_color_format(game, tmp) == ERROR)
		return (free_dp_rt(&tmp, ERROR));
	id = ft_strdup(tmp[0]);
	tmp2 = ft_strdup(tmp[1]);
	free_dp_rt(&tmp, 0);
	tmp = ft_split(tmp2, ',');
	free(tmp2);
	if (tmp == NULL || tmp[0] == NULL)
		return (free_dp_rt(&tmp, free_sp_rt(&id, putstr_perror(""))));
	if (is_valid_id_color(game, tmp, id) == ERROR)
		return (free_dp_rt(&tmp, free_sp_rt(&id, ERROR)));
	return (free_dp_rt(&tmp, free_sp_rt(&id, SUCCESS)));
}
