/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/29 04:18:59 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*read_log[OPEN_MAX - _SC_OPEN_MAX] = {NULL};
	t_gnl		dest;
	char		*buf;

	if (!initialize_gnl(fd, &dest, &buf, &read_log[fd]))
		return (NULL);
	if (!cat_to_line_break(&dest, read_log[fd], read_log[fd], BUFFER_SIZE)
		|| search_line_break(dest.str, BUFFER_SIZE))
	{
		free(buf);
		return (dest.str);
	}
	solve_get_next_line(fd, &dest, buf, read_log[fd]);
	free(buf);
	if (!dest.str || !dest.len)
	{
		if (dest.str && !dest.len)
			free(dest.str);
		free(read_log[fd]);
		read_log[fd] = NULL;
		return (NULL);
	}
	return (dest.str);
}
