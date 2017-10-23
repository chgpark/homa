/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 22:50:56 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 15:04:56 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	ft_spca(void)
{
	write(1, "[rush-02] [1] [1]", 17);
	write(1, " || ", 4);
	write(1, "[rush-03] [1] [1]", 17);
	write(1, " || ", 4);
	write(1, "[rush-04] [1] [1]\n", 18);
}

void	ft_spcb(int i, int r, int c)
{
	if (i)
	{
		write(1, "[rush-02] [1", 12);
		write(1, "] [", 3);
		ft_putnbr(c);
		write(1, "] || ", 5);
		write(1, "[rush-04] [1", 12);
		write(1, "] [", 3);
		ft_putnbr(c);
		write(1, "]\n", 2);
	}
	else
	{
		write(1, "[rush-03] [", 11);
		ft_putnbr(r);
		write(1, "] [1] || ", 9);
		write(1, "[rush-04] [", 11);
		ft_putnbr(r);
		write(1, "] [1]\n", 6);
	}
}

void	ft_print(int n, int r, int c)
{
	if (r <= 0 || c <= 0)
		write(1, "aucune\n", 7);
	else if ((n == 2 || n == 3 || n == 4) && r == 1 && c == 1)
		ft_spca();
	else if ((n == 2 || n == 4) && r == 1)
		ft_spcb(1, r, c);
	else if ((n == 3 || n == 4) && c == 1)
		ft_spcb(0, r, c);
	else
	{
		write(1, "[rush-0", 7);
		ft_putnbr(n);
		write(1, "] [", 3);
		ft_putnbr(r);
		write(1, "] [", 3);
		ft_putnbr(c);
		write(1, "]\n", 2);
	}
}
