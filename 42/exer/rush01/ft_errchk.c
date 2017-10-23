/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errchk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 10:07:46 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 18:10:15 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int		ft_chk_nbr(char **c)
{
	int		row;
	int		col;
	int		i;

	i = 0;
	row = 1;
	col = 0;
	while (row <= 9)
	{
		col = 0;
		while (RC)
		{
			if ((RC < '0' || RC > '9') && RC != '.')
				return (1);
			i++;
			col++;
		}
		row++;
	}
	if (row > 10 || col > 9)
		return (1);
	else if (i != 81)
		return (1);
	else
		return (0);
}

int		ft_errchk(int i, char **c)
{
	if (i != 10)
	{
		ft_putstr("Error\n");
		return (1);
	}
	else if (ft_chk_nbr(c))
	{
		ft_putstr("Error\n");
		return (1);
	}
	else
		return (0);
}

int		ft_filter(int input, int line, int n[81], int a)
{
	int		r;
	int		c;

	r = line / 9 - line / 9 % 3;
	while (++a <= 2)
	{
		c = line % 9 - line % 9 % 3 - 1;
		while (++c <= line % 9 - line % 9 % 3 + 2)
		{
			if (input == n[(r + a) * 9 + c])
				return (0);
		}
	}
	a = -1;
	while (++a <= 8)
	{
		if (input == n[a * 9 + line % 9])
			return (0);
	}
	while (--a >= 0)
	{
		if (input == n[line - line % 9 + a])
			return (0);
	}
	return (1);
}
