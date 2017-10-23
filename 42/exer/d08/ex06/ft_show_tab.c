/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:16:14 by cpark             #+#    #+#             */
/*   Updated: 2017/03/27 10:40:18 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_par.h"
#include <stdlib.h>

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

void	ft_show_tab(t_stock_par *par)
{
	int		j;
	int		k;

	while (par->str)
	{
		j = 0;
		while (par->copy[j])
			ft_putchar(par->copy[j++]);
		ft_putchar('\n');
		ft_putnbr(par->size_param);
		ft_putchar('\n');
		j = 0;
		while (par->tab[j])
		{
			k = 0;
			while (par->tab[j][k])
				ft_putchar(par->tab[j][k++]);
			ft_putchar('\n');
			j++;
		}
		par++;
	}
}
