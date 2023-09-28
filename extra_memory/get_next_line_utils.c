/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:31 by yoda              #+#    #+#             */
/*   Updated: 2023/09/29 08:52:11 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	realloc_c_sub(t_gnl *dest, char *src, size_t len_dst, size_t n)
{
	char	*new;
	size_t	size;

	if (((dest->len + n) / D_SIZE + 1) == SIZE_MAX / D_SIZE + 1)
		size = SIZE_MAX;
	else
		size = ((dest->len + n) / D_SIZE + 1) * D_SIZE;
	new = malloc(size);
	if (!new)
		return (0);
	while (--n != SIZE_MAX)
		new[len_dst + n] = src[n];
	while (--(len_dst) != SIZE_MAX)
		new[len_dst] = dest->str[len_dst];
	free(dest->str);
	dest->str = new;
	return (1);
}

static int	realloc_cat(t_gnl *dest, char *src, size_t len_dst, size_t n)
{
	size_t	i;

	if (SIZE_MAX - dest->len <= n + 1)
	{
		free(dest->str);
		return (0);
	}
	if (dest->len / D_SIZE == (dest->len + n) / D_SIZE)
	{
		i = n;
		while (--i != SIZE_MAX)
			dest->str[dest->len + i] = src[i];
	}
	else if (!realloc_c_sub(dest, src, len_dst, n))
		return (0);
	dest->str[dest->len + n] = '\0';
	return (1);
}

int	initialize_gnl(int fd, t_gnl *dest, char **buf, t_gnl *log)
{
	if (fd < 0 || OPEN_MAX - _SC_OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (0);
	dest->str = malloc(D_SIZE);
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
	if (!realloc_cat(dest, src, dest->len, i))
	{
		dest->str = NULL;
		return (0);
	}
	dest->len += i;
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
		if (!cat_to_line_break(dest, buf, log, r))
			return ;
		if (dest->len > 0 && dest->str[dest->len - 1] == '\n')
			line_break_detected = 1;
	}
}
