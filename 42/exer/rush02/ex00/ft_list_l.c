/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:55:23 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 11:50:12 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

t_list_l	*ft_create_elem_l(char data, int *nb)
{
	t_list_l		*rt;

	rt = malloc(sizeof(t_list_l));
	if (rt)
	{
		rt->next = NULL;
		rt->nb = nb;
		rt->data = data;
	}
	return (rt);
}

void		ft_cr_lst_l(t_list_l **begin_list, char data, int *nb)
{
	t_list_l		*list;
	t_list_l		*rt;

	rt = ft_create_elem_l(data, nb);
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

void		ft_list_clear_l(t_list_l **begin_list)
{
	t_list_l		*tmp;
	void			*chg;

	while (*begin_list)
	{
		tmp = *begin_list;
		chg = tmp->next;
		tmp->next = NULL;
		free(tmp);
		free(tmp->nb);
		*begin_list = chg;
	}
}

int			ft_list_size_l(t_list_l *begin_list)
{
	int				rt;

	rt = 0;
	while (begin_list)
	{
		rt = rt + begin_list->nb[0];
		begin_list = begin_list->next;
	}
	return (rt);
}
