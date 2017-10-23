/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:54:33 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 21:29:22 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_par.h"

struct	s_stock_par	*ft_param_to_tab(int ac, char **av)
{
	struct s_stock_par	*rt;
	struct s_stock_par	*tmp;
	int					i;
	int					j;

	rt = malloc(sizeof(struct s_stock_par) * (ac + 1));
	tmp = rt;
	i = -1;
	while (++i <= ac - 1)
	{
		rt->size_param = 0;
		j = -1;
		while (av[i][++j])
			rt->size_param += 1;
		rt->str = av[i];
		rt->copy = malloc(sizeof(char) * (j + 1));
		j = -1;
		while (av[i][++j])
			rt->copy[j] = av[i][j];
		rt->copy[j] = '\0';
		rt++->tab = ft_split_whitespaces(av[i]);
	}
	rt->str = NULL;
	return (tmp);
}
