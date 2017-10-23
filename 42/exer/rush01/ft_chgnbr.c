/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chgnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 12:16:18 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 17:02:58 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

void	ft_chrtonbr(char **c, int nbr[9][9])
{
	int		row;
	int		col;

	row = 1;
	while (row <= 9)
	{
		col = 0;
		while (RC)
		{
			if (RC == '.')
				nbr[row - 1][col] = 0;
			else
				nbr[row - 1][col] = RC - '0';
			col++;
		}
		row++;
	}
}

int		ft_sdk_rc_z(int line[81], int l, int i)
{
	while (++i <= 9)
	{
		if (ft_filter(i, l, line, -1))
		{
			line[l] = i;
			if (ft_sdk_line(line, l + 1))
				line[l] = 0;
		}
	}
	if (line[l] == 0)
		return (1);
	return (0);
}

int		ft_sdk_line(int line[81], int l)
{
	if (l >= 81)
		return (0);
	if (line[l] == 0)
		ft_sdk_rc_z(line, l, 0);
	else
	{
		if (ft_sdk_line(line, l + 1))
			return (1);
	}
	if (line[l] == 0)
		return (1);
	return (0);
}

void	ft_sdk(int nbr[9][9], int i)
{
	int		line[81];

	while (++i <= 80)
	{
		line[i] = nbr[i / 9][i % 9];
	}
	ft_sdk_line(line, 0);
	while (--i + 1 >= 0)
	{
		nbr[i / 9][i % 9] = line[i];
	}
}
