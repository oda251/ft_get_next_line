/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/28 22:53:18 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*read_log[OPEN_MAX - _SC_OPEN_MAX] = {NULL};
	char		*dest;
	char		*buf;

	if (!initialize_get_next_line(fd, &dest, &buf, &read_log[fd]))
		return (NULL);
	if (!cat_to_line_break(&dest, read_log[fd], read_log[fd], BUFFER_SIZE))
	{
		free(buf);
		return (NULL);
	}
	if (search_line_break(dest, BUFFER_SIZE))
	{
		free(buf);
		return (dest);
	}
	solve_get_next_line(fd, &dest, buf, read_log[fd]);
	free(buf);
	if (!dest || !*dest)
	{
		if (dest && !*dest)
			free(dest);
		free(read_log[fd]);
		read_log[fd] = NULL;
		return (NULL);
	}
	return (dest);
}
