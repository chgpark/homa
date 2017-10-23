/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:57:50 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 17:54:53 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_conv_inf(t_list_f *lt_f, t_inf *inf)
{
	int		i;

	i = 0;
	while (lt_f)
	{
		if (lt_f->data >= '0' && lt_f->data <= '9')
			inf->nl = inf->nl * 10 + lt_f->data - '0';
		else if (i == 0)
		{
			inf->e = lt_f->data;
			i++;
		}
		else if (i == 1)
		{
			inf->o = lt_f->data;
			i++;
		}
		else if (i == 2)
			inf->f = lt_f->data;
		lt_f = lt_f->next;
	}
}

int		**ft_conv_f(unsigned int *nb, t_inf *inf)
{
	int		**rt;
	int		i;
	int		j;

	i = -1;
	rt = malloc(sizeof(int *) * inf->nl);
	if (!rt)
		return (NULL);
	while (++i <= inf->nl - 1)
	{
		rt[i] = malloc(sizeof(int) * inf->nc);
		if (!rt[i])
			return (0);
	}
	i = -1;
	j = -1;
	while (++i <= inf->nc - 1)
	{
		if (!(i % 32))
			j++;
		if (i)
			rt[0][i] = nb[j] % 2 + rt[0][i - 1];
		else
			rt[0][i] = nb[j] % 2;
		nb[j] = nb[j] / 2;
	}
	return (rt);
}
