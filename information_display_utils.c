/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   information_display_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:00:45 by dogata            #+#    #+#             */
/*   Updated: 2020/12/23 19:30:20 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_f_color(t_game *game)
{
	int		i;
	char	*f_color;

	ft_putstr_fd("F ", 1);
	i = -1;
	while (++i < 3)
	{
		if (!(f_color = ft_itoa(game->conf.floor_color[i])))
		{
			putstr_perror("");
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd(f_color, 1);
		if (i != 2)
			ft_putchar_fd(',', 1);
		free_sp_rt(&f_color, 0);
	}
}

void	display_c_color(t_game *game)
{
	int		i;
	char	*c_color;

	ft_putstr_fd("C ", 1);
	i = -1;
	while (++i < 3)
	{
		if (!(c_color = ft_itoa(game->conf.ceilling_color[i])))
		{
			putstr_perror("");
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd(c_color, 1);
		if (i != 2)
			ft_putchar_fd(',', 1);
		free_sp_rt(&c_color, 0);
	}
}
