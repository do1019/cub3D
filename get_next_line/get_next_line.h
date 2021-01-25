/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 03:11:55 by dogata            #+#    #+#             */
/*   Updated: 2020/08/09 19:02:24 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define SUCCESS 1
# define ERROR -1
# define REACHED_EOF 0
# define FD_MAX 256

int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *str, int chr);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_free_strjoin(const char *s1, const char *s2);

#endif
