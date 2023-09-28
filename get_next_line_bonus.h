/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:33 by yoda              #+#    #+#             */
/*   Updated: 2023/09/28 22:10:38 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		initialize_get_next_line(int fd, char **dst, char **buf, char **r_log);
char	*get_next_line(int fd);
int		cat_to_line_break(char **dest, char *src, char *log, size_t r);
void	solve_get_next_line(int fd, char **dest, char *buf, char *read_log);
int		search_line_break(char *buf, size_t r);

#endif
