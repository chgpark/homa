/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:55:23 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 11:39:54 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*rt;

	rt = malloc(sizeof(t_list));
	if (rt)
	{
		rt->next = NULL;
		rt->data = data;
	}
	return (rt);
}

void	ft_cr_lst(t_list **begin_list, void *data)
{
	t_list		*list;
	t_list		*rt;

	rt = ft_create_elem(data);
	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = rt;
	}
	else
		*begin_list = rt;
}

void	ft_list_clear(t_list **begin_list)
{
	t_list	*tmp;
	void	*chg;

	while (*begin_list)
	{
		tmp = *begin_list;
		free(tmp->data);
		chg = tmp->next;
		tmp->next = NULL;
		free(tmp);
		*begin_list = chg;
	}
}

int		ft_list_size_c(t_list *begin_list)
{
	int		rt;

	rt = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		rt++;
	}
	return (rt);
}
