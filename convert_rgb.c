/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 07:44:38 by dogata            #+#    #+#             */
/*   Updated: 2020/12/24 22:46:48 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	ft_atoi_hex_to_dec(char *hex)
{
	size_t	ans;
	size_t	tmp;
	int		i;
	int		count;

	ans = 0;
	count = ft_strlen(hex);
	i = -1;
	while (++i < count)
	{
		if (*(hex + (count - i - 1)) <= 57 && 48 <= *(hex + (count - i - 1)))
			tmp = (*(hex + (count - i - 1))) - 48;
		else
			tmp = (*(hex + (count - i - 1))) - 55;
		ans += pow(16, i) * tmp;
	}
	return (ans);
}

static void		count_digit(int num, int *digit)
{
	*digit = 0;
	while (num)
	{
		num = num / 16;
		(*digit)++;
	}
}

static char		*convert(int num, char *str)
{
	int	rem;
	int digit;

	count_digit(num, &digit);
	while (digit || num)
	{
		rem = num % 16;
		if (10 > rem)
			str[digit-- - 1] = rem + 48;
		else
			str[digit-- - 1] = rem + 55;
		num = num / 16;
	}
	return (str);
}

static char		*ft_itoa_dec_to_hex(int num)
{
	char	*str;
	int		digit;

	if (num == 0)
		return (ft_strdup("00"));
	if (num < 0)
		return (NULL);
	count_digit(num, &digit);
	if (!(str = ft_calloc(digit + 1, sizeof(char))))
		return (NULL);
	return (convert(num, str));
}

ssize_t			convert_rgb_to_int(int *target)
{
	int			i;
	ssize_t		rt;
	char		*tmp[3];
	char		*hex;
	char		*hex_tmp;

	i = -1;
	while (++i < 3)
		tmp[i] = ft_itoa_dec_to_hex(target[i]);
	if (!(hex_tmp = ft_strjoin(tmp[0], tmp[1])))
		return (putstr_perror("Failed convert rgb"));
	if (!(hex = ft_strjoin(hex_tmp, tmp[2])))
		return (free_sp_rt(&hex_tmp, putstr_perror("Failed convert rgb")));
	rt = ft_atoi_hex_to_dec(hex);
	i = -1;
	while (++i < 3)
		free(tmp[i]);
	free(hex_tmp);
	free(hex);
	return (rt);
}
