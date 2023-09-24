/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:31 by yoda              #+#    #+#             */
/*   Updated: 2023/09/24 19:59:13 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_push_back(char *str, char c, size_t len)
{
	char	*dest;
	size_t	i;

	dest = malloc(len + 2);
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	dest[len + 1] = '\0';
	i = 0
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = c;
	free(str);
	return (dest)
}
