/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:04:48 by dogata            #+#    #+#             */
/*   Updated: 2020/12/25 07:49:51 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_flag_true(t_game *game, int num)
{
	if (num == 0 && game->conf.id_no_flag == true)
		return (putstr_error("Multiple NO identifier"));
	if (num == 1 && game->conf.id_so_flag == true)
		return (putstr_error("Multiple SO identifier"));
	if (num == 2 && game->conf.id_we_flag == true)
		return (putstr_error("Multiple WE identifier"));
	if (num == 3 && game->conf.id_ea_flag == true)
		return (putstr_error("Multiple EA identifier"));
	if (num == 4 && game->conf.id_s_flag == true)
		return (putstr_error("Multiple S identifier"));
	return (0);
}

static void	is_any_flag(t_game *game, int num)
{
	if (num == 0)
		game->conf.id_no_flag = true;
	if (num == 1)
		game->conf.id_so_flag = true;
	if (num == 2)
		game->conf.id_we_flag = true;
	if (num == 3)
		game->conf.id_ea_flag = true;
	if (num == 4)
		game->conf.id_s_flag = true;
}

static int	is_valid_texture_file(t_game *game, int *fd, char ***tmp, int num)
{
	char	*buf;
	char	*errmsg;

	errmsg = "Texture file does not have xpm extension";
	if ((*fd = open((*tmp)[1], O_RDONLY)) == ERROR)
		return (putstr_perror("Failed open texture file"));
	if (ft_strlen((*tmp)[1]) <= 4)
		return (putstr_perror("Invalid texture file"));
	if (!(buf = malloc(sizeof(char) * 1)))
		return (putstr_perror(""));
	if ((read(*fd, buf, 1)) == ERROR)
		return (free_sp_rt(&buf, putstr_perror("Failed open texture file")));
	if (ft_memcmp((*tmp)[1] + (ft_strlen((*tmp)[1]) - 4), ".xpm", 4))
		return (free_sp_rt(&buf, putstr_error(errmsg)));
	if (!(game->conf.texture_path[num] = ft_strdup((*tmp)[1])))
		return (free_sp_rt(&buf, putstr_perror("")));
	return (free_sp_rt(&buf, 0));
}

static int	is_valid_id_texture(t_game *game, char *line, char *id, int num)
{
	int		fd;
	char	**tmp;
	char	*errmsg;
	size_t	i;

	errmsg = "Invalid identifier / configuration file format";
	tmp = ft_split(line, ' ');
	if (tmp == NULL || tmp[0] == NULL)
		return (free_dp_rt(&tmp, putstr_perror("")));
	i = 0;
	while (tmp[i])
		i++;
	if (ft_memcmp(tmp[0], id, ft_strlen(id) + 1) || i != 2)
		return (free_dp_rt(&tmp, putstr_error(errmsg)));
	if (is_flag_true(game, num) == ERROR)
		return (free_dp_rt(&tmp, ERROR));
	if (is_valid_texture_file(game, &fd, &tmp, num) == ERROR)
		return (free_dp_rt(&tmp, ERROR));
	is_any_flag(game, num);
	return (free_dp_rt(&tmp, SUCCESS));
}

int			is_valid_id_textures(char *line, t_game *game)
{
	if (!ft_memcmp(line, "NO", 2))
		return (is_valid_id_texture(game, line, "NO", 0));
	if (!ft_memcmp(line, "SO", 2))
		return (is_valid_id_texture(game, line, "SO", 1));
	if (!ft_memcmp(line, "WE", 2))
		return (is_valid_id_texture(game, line, "WE", 2));
	if (!ft_memcmp(line, "EA", 2))
		return (is_valid_id_texture(game, line, "EA", 3));
	if (!ft_memcmp(line, "S", 1))
		return (is_valid_id_texture(game, line, "S", 4));
	return (putstr_error("Invalid identifier / configuration file format"));
}
