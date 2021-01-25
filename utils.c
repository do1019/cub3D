/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:47:41 by dogata            #+#    #+#             */
/*   Updated: 2020/12/23 02:26:14 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		putstr_error(char *s)
{
	ft_putendl_fd("\x1b[31mERROR\x1b[m", 2);
	ft_putendl_fd(s, 2);
	return (ERROR);
}

int		putstr_perror(char *s)
{
	ft_putendl_fd("\x1b[31mERROR\x1b[m", 2);
	perror(s);
	return (ERROR);
}

int		free_dp_rt(char ***tmp, int rt)
{
	int	array;

	array = -1;
	if (*tmp)
	{
		while ((*tmp)[++array])
		{
			free((*tmp)[array]);
			(*tmp)[array] = NULL;
		}
	}
	free(*tmp);
	*tmp = NULL;
	return (rt);
}

int		free_sp_rt(char **tmp, int rt)
{
	if (tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (rt);
}
