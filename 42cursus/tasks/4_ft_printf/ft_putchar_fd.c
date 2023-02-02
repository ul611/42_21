/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:21:00 by twilford          #+#    #+#             */
/*   Updated: 2020/11/05 00:21:02 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Outputs the character ’c’ to the given file descriptor.
**	Parameters
**	#1.  The character to output.
**	#2.  The file descriptor on which to write.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
