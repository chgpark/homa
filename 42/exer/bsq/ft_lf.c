/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:55:23 by cpark             #+#    #+#             */
/*   Updated: 2017/03/27 17:21:10 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

t_list_f	*ft_create_elem_f(char data)
{
	t_list_f		*rt;

	rt = malloc(sizeof(t_list_f));
	if (rt)
	{
		rt->next = NULL;
		rt->data = data;
	}
	return (rt);
}

void		ft_cr_lst_f(t_list_f **begin_list, char data)
{
	t_list_f		*list;
	t_list_f		*rt;

	rt = ft_create_elem_f(data);
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

void		ft_list_clear_f(t_list_f **begin_list)
{
	t_list_f		*tmp;
	void			*chg;

	while (*begin_list)
	{
		tmp = *begin_list;
		chg = tmp->next;
		tmp->next = NULL;
		free(tmp);
		*begin_list = chg;
	}
}

int			ft_list_size_f(t_list_f *begin_list)
{
	int				rt;

	rt = 0;
	while (begin_list)
	{
		rt += 1;
		begin_list = begin_list->next;
	}
	return (rt);
}
