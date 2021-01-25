/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_configuration_file.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:45:17 by dogata            #+#    #+#             */
/*   Updated: 2020/12/25 07:54:30 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_directory(char **argv, int fd)
{
	char *buf;
	char *errmsg;

	errmsg = "Failed open configuration file";
	if (!(buf = malloc(sizeof(char) * 1)))
		return (putstr_perror(""));
	if ((read(fd, buf, 1)) == ERROR)
		return (free_sp_rt(&buf, putstr_perror(errmsg)));
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) == ERROR)
		return (free_sp_rt(&buf, putstr_perror(errmsg)));
	return (free_sp_rt(&buf, 0));
}

static int	is_blank_line(char *line)
{
	while (*line)
	{
		if (*line == ' ')
			line++;
		else
			return (0);
	}
	return (SUCCESS);
}

static int	is_exists_all_identifier(t_game *game)
{
	if (game->conf.id_r_flag == true && game->conf.id_no_flag == true
		&& game->conf.id_so_flag && game->conf.id_we_flag == true
		&& game->conf.id_ea_flag == true && game->conf.id_s_flag == true)
		return (SUCCESS);
	return (0);
}

static int	is_valid_format(char *line, t_game *game)
{
	if (is_blank_line(line) && game->conf.map.map_search_started == false)
		return (SUCCESS);
	if (is_blank_line(line) && game->conf.map.map_search_started == true
		&& game->conf.map.map_end == false)
	{
		game->conf.map.map_end = true;
		return (SUCCESS);
	}
	else if (*line == 'R')
		return (is_valid_id_r(line, game));
	else if (!ft_memcmp(line, "NO", 2) || !ft_memcmp(line, "S", 1) ||
		!ft_memcmp(line, "WE", 2) || !ft_memcmp(line, "EA", 2))
		return (is_valid_id_textures(line, game));
	else if (*line == 'F' || *line == 'C')
		return (is_valid_id_colors(line, game));
	else if (is_exists_all_identifier(game) && game->conf.map.map_end == false)
		return (is_valid_map_format(line, game));
	return (putstr_error("Invalid configuration file format"));
}

int			is_valid_configuration_file(char **argv, t_game *game)
{
	char	*line;
	int		fd;
	int		rt;

	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == ERROR)
		return (putstr_perror("Failed to open the configuration file"));
	if ((is_directory(argv, fd)) == ERROR)
		return (ERROR);
	rt = SUCCESS;
	while ((get_next_line(fd, &line)) > 0 && rt == SUCCESS)
	{
		if ((rt = is_valid_format(line, game)) == ERROR)
			return (free_sp_rt(&line, ERROR));
		free_sp_rt(&line, 0);
	}
	if ((rt = is_valid_format(line, game)) == ERROR)
		return (free_sp_rt(&line, ERROR));
	free_sp_rt(&line, 0);
	close(fd);
	return (is_valid_map(game));
}
