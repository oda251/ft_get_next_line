/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:31 by yoda              #+#    #+#             */
/*   Updated: 2023/09/26 22:41:40 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*realloc_cat(char **str, char *src, size_t len_str, size_t n)
{
	char	*dest;

	if (SIZE_MAX - len_str <= n)
	{
		free(*str);
		return (NULL);
	}
	dest = malloc(len_str + n + 1);
	if (!dest)
	{
		free(*str);
		return (NULL);
	}
	dest[len_str + n] = '\0';
	while (--n != SIZE_MAX)
		dest[len_str + n] = src[n];
	while (--len_str != SIZE_MAX)
		dest[len_str] = (*str)[len_str];
	free(*str);
	return (dest);
}

int	search_line_break(char *buf, size_t r)
{
	size_t	i;

	i = 0;
	while (i < r && buf[i])
	{
		if (buf[i++] == '\n')
			return (1);
	}
	return (0);
}

int	initialize_get_next_line(int fd, char **dest, char **buf, char **read_log)
{
	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	*dest = malloc(1);
	if (!*dest)
		return (0);
	**dest = '\0';
	*buf = malloc(BUFFER_SIZE);
	if (!*buf)
	{
		free(*dest);
		return (0);
	}
	if (!*read_log)
	{
		*read_log = malloc(BUFFER_SIZE);
		if (!*read_log)
		{
			free(*dest);
			free(*buf);
			return (0);
		}
		**read_log = '\0';
	}
	return (1);
}

int	cat_to_line_break(char **dest, char *src, char *log, size_t r)
{
	size_t	i;
	size_t	tmp;
	size_t	len_dest;

	len_dest = 0;
	while ((*dest)[len_dest])
		len_dest++;
	i = 0;
	while (i < r && src[i])
	{
		if (src[i++] == '\n')
			break ;
	}
	*dest = realloc_cat(dest, src, len_dest, i);
	if (!*dest)
	{
		free(*dest);
		return (0);
	}
	tmp = i--;
	while (++i < r && src[i])
		log[i - tmp] = src[i];
	log[i - tmp] = '\0';
	return (1);
}

void	solve_get_next_line(int fd, char **dest, char *buf, char *read_log)
{
	ssize_t	r;
	int		line_break_detected;

	line_break_detected = 0;
	while (!line_break_detected)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(*dest);
			*dest = NULL;
			return ;
		}
		else if (r == 0)
			break ;
		line_break_detected = search_line_break(buf, r);
		cat_to_line_break(dest, buf, read_log, r);
	}
}
