/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:12:13 by twilford          #+#    #+#             */
/*   Updated: 2020/11/28 15:12:15 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void	ft_bzero(char *s, int n);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2, int start, int end);
int		free_if_error(char *s1, char *s2, char *s3);
int		where_is_newline(char *buf);
int		if_nl_in_rsd(char **line, char **rsd, int nl);
int		ft_tmp(char **rsd, char **buf, int nl);
int		ft_tmp_rsd(char **rsd, char **buf, char **line, int nl);
int		last(char **rsd, int a, int nl);
int		get_next_line(int fd, char **line);

#endif
