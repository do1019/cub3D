/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:50:48 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 20:50:50 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprlst	*spr_lstnew(double x, double y)
{
	t_sprlst *lst;

	if (!(lst = (t_sprlst *)malloc(sizeof(t_sprlst))))
		return (NULL);
	lst->x = x;
	lst->y = y;
	lst->distance = 0;
	return (lst);
}

static void	bubble_sort(t_list **current)
{
	t_sprlst *current_spr;
	t_sprlst *next_spr;
	t_sprlst *tmp;

	current_spr = (*current)->content;
	next_spr = (*current)->next->content;
	if (current_spr->distance < next_spr->distance)
	{
		tmp = (*current)->content;
		(*current)->content = (*current)->next->content;
		(*current)->next->content = tmp;
	}
	(*current) = (*current)->next;
}

void		sort_sprites(t_game *game)
{
	t_list	*current;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i++ < game->spr.sprite_count - 1)
	{
		current = game->spr.head;
		while (j++ < game->spr.sprite_count - 1)
			bubble_sort(&current);
		j = 0 + i;
	}
}
