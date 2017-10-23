/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 19:57:44 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 11:51:24 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse_fun(t_list *begin_list)
{
	int		count;
	int		i;
	void	*chg;
	t_list	*tmp;

	count = 0;
	tmp = begin_list;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	while (--count > 0)
	{
		tmp = begin_list;
		i = count;
		while (i--)
		{
			chg = tmp->data;
			tmp->data = tmp->next->data;
			tmp = tmp->next;
			tmp->data = chg;
		}
	}
}
