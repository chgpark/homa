/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:55:23 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 11:55:25 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_back(t_list **begin_list, void *data)
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
