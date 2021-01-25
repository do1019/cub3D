/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:50:55 by dogata            #+#    #+#             */
/*   Updated: 2020/12/26 06:32:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_buffer_init(t_game *game)
{
	int	i;

	i = -1;
	if (!(game->tex.texture = malloc(sizeof(int *) * TEX_NUM)))
	{
		putstr_perror("");
		exit(EXIT_FAILURE);
	}
	while (++i < TEX_NUM)
	{
		if (!(game->tex.texture[i] =
			ft_calloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int))))
		{
			free(game->tex.texture);
			putstr_perror("");
			exit(EXIT_FAILURE);
		}
	}
}

int		load_image(t_game *game, int *texture, char *path)
{
	int	y;
	int	x;

	if (!(game->img.img = mlx_xpm_file_to_image(game->mlx,
			path, &game->img.img_width, &game->img.img_height)))
		return (putstr_error("Failed xpm file to image / Invalid xpm file"));
	if (game->img.img_height != 64 || game->img.img_width != 64)
		return (putstr_error("Invalid xpm file / 64×64 xpm file only enabled"));
	game->img.addr = (int *)mlx_get_data_addr(game->img.img,
		&game->img.bpp, &game->img.line_length, &game->img.endian);
	y = -1;
	while (++y < (game)->img.img_height)
	{
		x = -1;
		while (++x < (game)->img.img_width)
			texture[(game)->img.img_width * y + x] =
				(game)->img.addr[(game)->img.img_width * y + x];
	}
	mlx_destroy_image((game)->mlx, (game)->img.img);
	return (0);
}

int		load_texture(t_game *game)
{
	int i;

	texture_buffer_init(game);
	i = -1;
	while (++i < TEX_NUM)
	{
		if ((load_image(game, game->tex.texture[i],
			game->conf.texture_path[i])) == ERROR)
			exit(EXIT_FAILURE);
	}
	return (0);
}
