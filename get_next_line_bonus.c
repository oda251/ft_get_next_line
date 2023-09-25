/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/25 21:58:46 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*read_log[FOPEN_MAX] = {NULL};
	char		*dest;
	char		*buf;

	if (!initialize_get_next_line(fd, &dest, &buf, &read_log[fd]))
		return (NULL);
	if (!cat_to_line_break(&dest, read_log[fd], read_log[fd], BUFFER_SIZE))
	{
		free(buf);
		return (NULL);
	}
	solve_get_next_line(fd, &dest, buf, read_log[fd]);
	free(buf);
	if (!dest)
	{
		free(read_log[fd]);
		return (NULL);
	}
	if (!*dest)
	{
		free(dest);
		free(read_log[fd]);
		return (NULL);
	}
	return (dest);
}

//#include <fcntl.h>
//int main()
//{
//	char *line;
//	char *line2;
//	char *line3;
//	int fd = open("test.txt", O_RDONLY);
//	int fd2 = open("test2.txt", O_RDONLY);
//	int fd3 = open("test3.txt", O_RDONLY);
//	while (1)
//	{
//		line = get_next_line(fd);
//		line2 = get_next_line(fd2);
//		line3 = get_next_line(fd3);
//		if (!line)
//			break;
//		printf("%s", line);
//		printf("%s", line2);
//		printf("%s", line3);
//		free(line);
//		free(line2);
//		free(line3);
//	}
//	close(fd);
//	return (0);
//}