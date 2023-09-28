/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:31 by yoda              #+#    #+#             */
/*   Updated: 2023/09/29 05:46:03 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*realloc_cat(t_gnl *dest, char *src, size_t len_dst, size_t n)
{
	char		*new;

	if (SIZE_MAX - len_dst <= n)
	{
		free(dest->str);
		return (NULL);
	}
	new = malloc(len_dst + n + 1);
	if (!new)
	{
		free(dest->str);
		return (NULL);
	}
	new[len_dst + n] = '\0';
	while (--n != SIZE_MAX)
		new[len_dst + n] = src[n];
	while (--(len_dst) != SIZE_MAX)
		new[len_dst] = dest->str[len_dst];
	free(dest->str);
	dest->str = new;
	return (new);
}

int	search_line_break(char *str, size_t r)
{
	size_t	i;

	i = 0;
	while (i < r && str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

int	initialize_gnl(int fd, t_gnl *dest, char **buf, t_gnl *log)
{
	if (fd < 0 || OPEN_MAX - _SC_OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (0);
	dest->str = malloc(1);
	if (!dest->str)
		return (0);
	dest->len = 0;
	*buf = malloc(BUFFER_SIZE);
	if (!*buf)
	{
		free(dest->str);
		return (0);
	}
	if (!log->str)
	{
		log->str = malloc(BUFFER_SIZE);
		if (!log->str)
		{
			free(dest->str);
			free(*buf);
			return (0);
		}
		log->len = 0;
	}
	return (1);
}

int	cat_to_line_break(t_gnl *dest, char *src, t_gnl *log, size_t r)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	while (i < r)
	{
		if (src[i++] == '\n')
			break ;
	}
	dest->str = realloc_cat(dest, src, dest->len, i);
	dest->len += i;
	if (!dest->str)
	{
		free(dest->str);
		dest->str = NULL;
		return (0);
	}
	tmp = i--;
	while (++i < r)
		log->str[i - tmp] = src[i];
	log->len = i - tmp;
	return (1);
}

void	solve_get_next_line(int fd, t_gnl *dest, char *buf, t_gnl *log)
{
	ssize_t	r;
	int		line_break_detected;

	line_break_detected = 0;
	while (!line_break_detected)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(dest->str);
			dest->str = NULL;
			return ;
		}
		else if (r == 0)
			break ;
		line_break_detected = search_line_break(buf, r);
		cat_to_line_break(dest, buf, log, r);
	}
}
