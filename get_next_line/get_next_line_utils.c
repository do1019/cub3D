/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 09:46:01 by dogata            #+#    #+#             */
/*   Updated: 2020/11/05 17:53:25 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int chr)
{
	size_t count;

	count = ft_strlen(str);
	count = count + 1;
	while (count-- != 0)
	{
		if (*(unsigned char *)str == (unsigned char)chr)
			return ((char*)str);
		str++;
	}
	return (NULL);
}

char	*ft_free_strjoin(const char *s1, const char *s2)
{
	char	*cstr;
	size_t	s1len;
	size_t	s2len;
	int		count;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(cstr = malloc(sizeof(char) * (s1len + s2len + 1))))
	{
		free((char *)s1);
		return (NULL);
	}
	count = -1;
	while ((int)s1len > ++count)
		cstr[count] = s1[count];
	count = -1;
	while (((int)s1len + (int)s2len + 1) > ((int)s1len + ++count))
		cstr[(int)s1len + count] = s2[count];
	free((char *)s1);
	return (cstr);
}
