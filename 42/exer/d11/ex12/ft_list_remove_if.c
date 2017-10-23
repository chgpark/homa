/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:24:45 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 11:11:48 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reif(t_list *bf, t_list *prs, void *data_ref, int (*cmp)())
{
	prs = bf->next;
	while (prs)
	{
		if ((*cmp)(prs->data, data_ref) == 0)
		{
			prs->data = NULL;
			bf->next = prs->next;
			prs->next = NULL;
			free(prs);
			prs = bf->next;
		}
		else
		{
			bf = prs;
			prs = prs->next;
		}
	}
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*bf;
	t_list	*prs;

	bf = *begin_list;
	if (bf && bf->next)
	{
		prs = bf->next;
		ft_list_reif(bf, prs, data_ref, cmp);
	}
	if (bf && bf->data == NULL && data_ref == NULL)
	{
		*begin_list = bf->next;
		bf->next = NULL;
		free(bf);
	}
	else if (bf && bf->data == NULL)
		return ;
	else if (bf && (*cmp)(bf->data, data_ref) == 0)
	{
		*begin_list = bf->next;
		bf->data = NULL;
		bf->next = NULL;
		free(bf);
	}
}
