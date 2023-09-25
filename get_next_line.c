/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:07 by yoda              #+#    #+#             */
/*   Updated: 2023/09/24 19:58:54 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_push_back(char *str, char c, size_t len);

char	*get_next_line(int fd)
{
	char	*dest;
	char	*buf;
	size_t	len;
	int		r;

	dest = malloc(1);
	*dest = '\0';
	if (!dest)
		return (NULL);
	len = 0;
	while (1)
	{
		r = read(fd, buf, 1);
		if (r < 0)
		{
			if (len == 0)
				return (NULL);
			break ;
		}
		printf("%c", *buf);
		dest = str_push_back(dest, *buf, len);
		if (!dest)
			return (NULL);
		if (*buf == '\n')
			break ;
		len++;
	}
	return (dest);
}