/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bmp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 06:55:43 by dogata            #+#    #+#             */
/*   Updated: 2020/12/23 08:19:37 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*dec_to_rgb(unsigned int num)
{
	int r;
	int g;
	int b;
	int *rt;

	r = num / 65536;
	g = (num - r * 65536) / 256;
	b = num - r * 65536 - g * 256;
	if (!(rt = malloc(sizeof(int) * 3)))
		return (NULL);
	rt[0] = r;
	rt[1] = g;
	rt[2] = b;
	return (rt);
}

t_rgb	*create_rgb_array(int width, int height)
{
	t_rgb *rgb_array;

	if (!(rgb_array = (t_rgb *)ft_calloc(width * height, sizeof(t_rgb))))
		return (NULL);
	return (rgb_array);
}

void	output_bmp_mem_allocation(t_game *game, int fd)
{
	game->bmp.bmp_line = ft_calloc(game->bmp.r_width, sizeof(unsigned char));
	game->bmp.tmp_line = ft_calloc(game->bmp.r_width, sizeof(unsigned int));
	game->img.rgb =
		create_rgb_array(game->conf.x_render_size, game->conf.y_render_size);
	if (!game->bmp.bmp_line || !game->bmp.tmp_line || !game->img.rgb)
	{
		close(fd);
		putstr_perror("");
		free(game->bmp.bmp_line);
		free(game->bmp.tmp_line);
		free(game->img.rgb);
		exit(EXIT_FAILURE);
	}
}

void	store_rgb_info_to_rgb_struct(t_game *game, int i, int j)
{
	game->img.rgb[i * game->conf.x_render_size + j].b = game->bmp.rgb[2];
	game->img.rgb[i * game->conf.x_render_size + j].g = game->bmp.rgb[1];
	game->img.rgb[i * game->conf.x_render_size + j].r = game->bmp.rgb[0];
}

void	store_rgb_info_to_bmp_line(t_game *game, int i, int j)
{
	game->bmp.bmp_line[j * 3] =
		game->img.rgb[(game->conf.y_render_size - i - 1) *
			game->conf.x_render_size + j].b;
	game->bmp.bmp_line[j * 3 + 1] =
		game->img.rgb[(game->conf.y_render_size - i - 1) *
			game->conf.x_render_size + j].g;
	game->bmp.bmp_line[j * 3 + 2] =
		game->img.rgb[(game->conf.y_render_size - i - 1) *
			game->conf.x_render_size + j].r;
}
