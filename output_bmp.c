/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 01:44:58 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 16:20:33 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		get_pixel_color_from_img_addr(t_game *game)
{
	int i;
	int j;

	i = -1;
	while (++i < game->conf.y_render_size)
	{
		j = -1;
		while (++j < game->conf.x_render_size)
			game->bmp.tmp_line[j] =
				game->img.addr[j + (game->conf.x_render_size * i)];
		j = -1;
		while (++j < game->conf.x_render_size)
		{
			if (!(game->bmp.rgb = dec_to_rgb(game->bmp.tmp_line[j])))
			{
				putstr_perror("");
				exit(EXIT_FAILURE);
			}
			store_rgb_info_to_rgb_struct(game, i, j);
			free(game->bmp.rgb);
		}
	}
}

static void		write_rgb_info_to_bmp(t_game *game, int fd)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < game->conf.y_render_size)
	{
		j = -1;
		while (++j < game->conf.x_render_size)
			store_rgb_info_to_bmp_line(game, i, j);
		j = game->conf.x_render_size * 3;
		while (j < game->bmp.r_width)
			game->bmp.bmp_line[j++] = 0;
		write(fd, game->bmp.bmp_line, game->bmp.r_width);
	}
}

void			output_bmp(t_game *game)
{
	int	fd;

	if ((fd = open("cub3d.bmp",
		O_RDWR | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG)) == ERROR)
	{
		putstr_perror("");
		exit(EXIT_FAILURE);
	}
	bmp_struct_init(game);
	write(fd, game->bmp.header_buf, HEADER_SIZE);
	output_bmp_mem_allocation(game, fd);
	get_pixel_color_from_img_addr(game);
	write_rgb_info_to_bmp(game, fd);
	close(fd);
	free(game->bmp.bmp_line);
	free(game->bmp.tmp_line);
	free(game->img.rgb);
	ft_putendl_fd("\x1b[32mBmp file creation complete.\x1b[m\n", 1);
	exit(EXIT_SUCCESS);
}
