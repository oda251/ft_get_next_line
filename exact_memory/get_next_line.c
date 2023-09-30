/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/30 18:17:00 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	logs[OPEN_MAX - _SC_OPEN_MAX] = {{0}};
	t_gnl			dest;
	char			*buf;

	if (!initialize_gnl(fd, &dest, &buf, &logs[fd]))
		return (NULL);
	if (!cat_to_line_break(&dest, logs[fd].str, &logs[fd], logs[fd].len)
		|| search_line_break(dest.str, BUFFER_SIZE))
	{
		free(buf);
		return (dest.str);
	}
	solve_get_next_line(fd, &dest, buf, &logs[fd]);
	free(buf);
	if (!dest.str || !dest.len)
	{
		if (dest.str && !dest.len)
			free(dest.str);
		free(logs[fd].str);
		logs[fd].str = NULL;
		return (NULL);
	}
	return (dest.str);
}

/* normal */
/* echo -n -e '012\n\n345\n\n678\n\n901' > test.txt */
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd;
// 	fd = open("test.txt", O_RDONLY);
// 	if	(line = get_next_line(fd))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
/* null_EOF_value */
/* echo -n -e '\x00\xff1234' > test.txt */
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd;
// 	fd = open("test.txt", O_RDONLY);
// 	while	(line = get_next_line(fd))
// 	{
// 		for(int i=0; i<7; i++)
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