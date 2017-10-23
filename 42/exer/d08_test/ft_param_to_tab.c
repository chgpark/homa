/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:54:33 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 16:39:21 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_par.h"

t_stock_par	*ft_param_to_tab(int ac, char **av)
{
	t_stock_par			*rt;
	int					i;
	int					j;

	rt = malloc(sizeof(struct s_stock_par) * ac);
	i = -1;
	while (++i <= ac - 1)
	{
		rt[i].size_param = 0;
		j = -1;
		while (av[i][++j])
			rt[i].size_param += 1;
		rt[i].str = av[i];
		rt[i].copy = malloc(sizeof(char) * (j + 1));
		j = -1;
		while (av[i][++j])
			rt[i].copy[j] = av[i][j];
		rt[i].copy[j] = '\0';
		rt[i].tab = ft_split_whitespaces(av[i]);
	}
	return (rt);
}
