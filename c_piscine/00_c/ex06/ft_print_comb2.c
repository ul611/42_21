/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 22:59:26 by twilford          #+#    #+#             */
/*   Updated: 2020/09/18 11:38:28 by twilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_digits_and_count_l(int i, int j, int k, int l)
{
	write(1, i + '0', 1);
	write(1, j + '0', 1);
	write(1, " ", 1);
	write(1, k + '0', 1);
	write(1, l + '0', 1);
	write(1, ", ", 2);
	l++;
}

void	two_while(int i, int j, int k, int l)
{
	while (j <= 7)
	{
		j++;
		if (j == 9)
		{
			k = i;
			l = -1;
		}
		else
		{
			k = i - 1;
			l = j;
		}
		while (k <= 9)
		{
			k++;
			while (l <= 9)
			{
				write_digits_and_count_l(i, j, k, l);
			}
		}
	}
}

void	ft_pre_print_comb2(int k, int l)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (i <= 9)
	{
		i++;
		two_while(i, j, k, l);
	}
}

void	ft_print_comb2(void)
{
	ft_pre_print_comb2();
	write(1, "98 99\n", 6);
}
