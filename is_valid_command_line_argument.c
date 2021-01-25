/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_command_line_argument.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:29:09 by dogata            #+#    #+#             */
/*   Updated: 2020/12/26 06:32:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_valid_command_line_argument(int argc, char **argv, t_game *game)
{
	if (argc == 2 || argc == 3)
	{
		game_struct_init(game);
		if (ft_strlen(argv[1]) <= 4 ||
			!ft_memcmp(argv[1] + (ft_strlen(argv[1]) - 5), "/.cub", 5))
			return (putstr_error("Invalid configuration file"));
		if (!ft_memcmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
		{
			if (argc == 2)
				return (is_valid_configuration_file(argv, game));
			else if (!ft_memcmp(argv[2], "--save", 7))
			{
				game->save_flag = true;
				return (is_valid_configuration_file(argv, game));
			}
			else
				return
					(putstr_error("Second argument is valid only for --save"));
		}
		else
			return (putstr_error("Invalid configuration file"));
	}
	return (putstr_error("Invalid argument"));
}
