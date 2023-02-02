/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:51:37 by twilford          #+#    #+#             */
/*   Updated: 2020/09/17 22:57:56 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	digits(char *d)
{
	int		i;

	i = 0;
	while (i <= 9)
	{
		d[i] = i + '0';
		i++;
	}
}

void	ft_pre_print_comb(void)
{
	int		i;
	int		j;
	int		k;
	char	d[10];

	i = 0;
	digits(d);
	while (i <= 6)
	{
		i++;
		j = i;
		while (j <= 8)
		{
			j++;
			k = j;
			while (k <= 9)
			{
				k++;
				write(1, &d[i - 1], 1);
				write(1, &d[j - 1], 1);
				write(1, &d[k - 1], 1);
				write(1, ", ", 2);
			}
		}
	}
}

void	ft_print_comb(void)
{
	ft_pre_print_comb();
	write(1, "789\n", 4);
}
