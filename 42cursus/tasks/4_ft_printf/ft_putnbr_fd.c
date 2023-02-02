/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:21:25 by twilford          #+#    #+#             */
/*   Updated: 2020/11/05 00:21:26 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Outputs the integer ’n’ to the given file descriptor.
**	Parameters
**	#1.  The integer to output.
**	#2.  The file descriptor on which to write.
*/

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	d;
	long int		l;
	char			towrite;

	l = 1;
	d = n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		d = -n;
	}
	while (l <= d)
		l *= 10;
	while (l > 1)
	{
		l /= 10;
		towrite = (d / l) + '0';
		write(fd, &towrite, 1);
		d %= l;
	}
}
