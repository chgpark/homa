/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:48:50 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 11:48:41 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_st(t_list *stp_b, int (*cmp)(), int i)
{
	t_list	*bf;
	t_list	*prs;

	while (--i)
	{
		bf = stp_b;
		prs = bf->next;
		while (prs->next)
		{
			if ((*cmp)(prs->data, prs->next->data) > 0)
			{
				bf->next = prs->next;
				prs->next = prs->next->next;
				bf->next->next = prs;
				bf = bf->next;
			}
			else
			{
				bf = prs;
				prs = prs->next;
			}
		}
	}
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	int		i;
	t_list	*bf;
	t_list	*prs;

	i = 0;
	bf = *begin_list;
	while (bf)
	{
		bf = bf->next;
		i++;
	}
	bf = *begin_list;
	if (bf && bf->next)
	{
		ft_list_st(bf, cmp, i);
		if ((*cmp)(bf->data, bf->next->data) > 0)
		{
			prs = bf->next;
			bf->next = prs->next;
			prs->next = bf;
			*begin_list = prs;
		}
		bf = *begin_list;
		ft_list_st(bf, cmp, i);
	}
}
