/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoda <yoda@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:54:33 by yoda              #+#    #+#             */
/*   Updated: 2023/09/25 21:59:05 by yoda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

int		initialize_get_next_line(int fd, char **dst, char **buf, char **r_log);
char	*get_next_line(int fd);
int		cat_to_line_break(char **dest, char *src, char *log, size_t r);
void	solve_get_next_line(int fd, char **dest, char *buf, char *read_log);

#endif
