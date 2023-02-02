/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:11:21 by twilford          #+#    #+#             */
/*   Updated: 2020/11/28 15:11:33 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		if_nl_in_rsd(char **line, char **rsd, int nl)
{
	char	*tmp;

	if (!(*line = ft_strjoin(0, *rsd, 0, nl)))
		return (free_if_error(*rsd, 0, 0));
	if (!(tmp = ft_strjoin(0, *rsd, nl + 1, ft_strlen(*rsd))))
		return (free_if_error(*line, *rsd, 0));
	free(*rsd);
	*rsd = tmp;
	return (1);
}

int		ft_tmp(char **rsd, char **buf, int nl)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(*rsd, *buf, 0, nl)))
		return (free_if_error(*buf, *rsd, 0));
	free(*rsd);
	*rsd = tmp;
	ft_bzero(*buf, (int)BUFFER_SIZE);
	return (1);
}

int		ft_tmp_rsd(char **rsd, char **buf, char **line, int nl)
{
	char	*tmp;

	ft_bzero(*rsd, ft_strlen(*rsd));
	if (!(tmp = ft_strjoin(*rsd, *buf, nl + 1, ft_strlen(*buf))))
		return (free_if_error(*line, *rsd, *buf));
	free(*rsd);
	*rsd = tmp;
	free(*buf);
	return (1);
}

int		last(char **rsd, int a, int nl)
{
	if ((a < BUFFER_SIZE) && (nl == a))
	{
		free(*rsd);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			a;
	char		*buf;
	static char	*rsd = NULL;
	int			nl;

	if ((fd < 0) || !(line) || (BUFFER_SIZE <= 0))
		return (-1);
	if (rsd && ((nl = where_is_newline(rsd)) < ft_strlen(rsd)))
		return (if_nl_in_rsd(line, &rsd, nl));
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (free_if_error(rsd, 0, 0));
	ft_bzero(buf, (int)(BUFFER_SIZE + 1));
	if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
		return (free_if_error(rsd, buf, 0));
	while ((nl = where_is_newline(buf)) == BUFFER_SIZE)
	{
		if (ft_tmp(&rsd, &buf, nl) < 1)
			return (free_if_error(buf, rsd, 0));
		if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
			return (free_if_error(buf, rsd, 0));
	}
	if (!(*line = ft_strjoin(rsd, buf, 0, nl)))
		return (free_if_error(buf, rsd, 0));
	return ((ft_tmp_rsd(&rsd, &buf, line, nl) < 1) ? (-1) : last(&rsd, a, nl));
}
