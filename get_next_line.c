/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/29 04:18:24 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd;

// 	fd = open("test.txt", O_RDONLY);
// 	while	(line = get_next_line(fd))
// 	{
// 		for(int i=0; i<6; i++)
// 		{
// 			if (0x20 <= line[i] && line[i] <= 0x7e)
// 				printf("%c", line[i]);
// 			else
// 				printf("[%d]", line[i]);
// 		}
// 		free(line);
// 	}	
// 	close(fd);
// 	return (0);
// }
// echo -n -e '\x001234' >> test.txt