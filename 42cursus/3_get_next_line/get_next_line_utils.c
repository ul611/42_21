/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:11:53 by twilford          #+#    #+#             */
/*   Updated: 2020/11/28 15:11:56 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(char *s, int n)
{
	char	*ptr;

	if (s)
	{
		ptr = s + n;
		while (s != ptr)
			*s++ = '\0';
	}
}

int		ft_strlen(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s++)
		;
	return ((int)(s - tmp - 1));
}

char	*ft_strjoin(char *s1, char *s2, int start, int end)
{
	char	*join;
	int		len_all;
	int		len_2;

	len_2 = (end - start) * (end >= start) + 0 * (end < start);
	len_all = ft_strlen(s1) + len_2;
	if (!(join = (char *)malloc(sizeof(char) * (len_all + 1))))
	{
		return (0);
	}
	ft_bzero(join, (len_all + 1));
	if (s1)
	{
		while (*s1)
			*join++ = *s1++;
	}
	while (start < end)
		*join++ = s2[start++];
	return (join - len_all);
}

int		free_if_error(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (-1);
}

int		where_is_newline(char *buf)
{
	char	*iter;

	if (!buf)
		return (0);
	iter = buf;
	while (*iter)
	{
		if (*iter == '\n')
			return (iter - buf);
		iter++;
	}
	return (iter - buf);
}
