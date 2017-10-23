/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 10:03:42 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 17:19:35 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int		main(int argc, char **argv)
{
	int		sdk[9][9];
	int		cnt[9][9];
	int		count;

	count = 0;
	if (ft_errchk(argc, argv))
		return (0);
	ft_chrtonbr(argv, cnt);
	ft_count(cnt, -1, &count);
	if (count == 1)
	{
		ft_chrtonbr(argv, sdk);
		ft_sdk(sdk, -1);
		ft_putnbr(sdk);
	}
	else
		ft_putstr("Error\n");
	return (0);
}
