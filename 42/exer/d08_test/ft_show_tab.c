/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:16:14 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 16:05:55 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_par.h"

void	ft_putchar(char c);

void	ft_putnbr(int n)
{
	if (n > 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
#include <stdio.h>
void	ft_show_tab(t_stock_par *par)
{
	int		i;
	int		j;
	int		k;
	int		m;

	m = 0;
	i = 0;
	while ()
	{
		j = 0;
		while (par[i].copy[j])
			ft_putchar(par[i].copy[j++]);
		ft_putchar('\n');
		ft_putnbr(par[i].size_param);
		ft_putchar('\n');
		j = 0;
		while (par[i].tab[j])
		{
			k = 0;
			while (par[i].tab[j][k])
				ft_putchar(par[i].tab[j][k++]);
			ft_putchar('\n');
			j++;
		}
		i++;
	}
}
