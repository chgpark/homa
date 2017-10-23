/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chgnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 12:16:18 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 17:23:14 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int		ft_sdk_rc_count(int line[81], int l, int i, int *count)
{
	while (++i <= 9)
	{
		if (ft_filter(i, l, line, -1))
		{
			line[l] = i;
			if (ft_sdk_count(line, l + 1, count))
				line[l] = 0;
		}
	}
	if (line[l] == 0)
		return (1);
	return (0);
}

int		ft_sdk_count(int line[81], int l, int *count)
{
	if (l >= 81)
	{
		if (*count >= 2)
			return (0);
		*count += 1;
		return (1);
	}
	if (line[l] == 0)
		ft_sdk_rc_count(line, l, 0, count);
	else
	{
		if (ft_sdk_count(line, l + 1, count))
			return (1);
	}
	if (line[l] == 0)
		return (1);
	return (0);
}

void	ft_count(int nbr[9][9], int i, int *count)
{
	int		line[81];

	while (++i <= 80)
	{
		line[i] = nbr[i / 9][i % 9];
	}
	ft_sdk_count(line, 0, count);
	while (--i + 1 >= 0)
	{
		nbr[i / 9][i % 9] = line[i];
	}
}
