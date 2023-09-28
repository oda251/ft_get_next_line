/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:33 by yoda              #+#    #+#             */
/*   Updated: 2023/09/29 05:28:55 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# ifndef SIZE_MAX
#  define SIZE_MAX ULONG_MAX
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	char		*str;
	size_t		len;
}	t_gnl;
int		initialize_gnl(int fd, t_gnl *dst, char **buf, t_gnl *log);
char	*get_next_line(int fd);
int		cat_to_line_break(t_gnl *dest, char *src, t_gnl *log, size_t r);
void	solve_get_next_line(int fd, t_gnl *dest, char *buf, t_gnl *log);
int		search_line_break(char *buf, size_t r);

#endif
