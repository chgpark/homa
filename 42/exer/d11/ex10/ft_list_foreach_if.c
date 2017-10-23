/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:34:15 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 11:57:43 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
		void *data_ref, int (*cmp)())
{
	if (data_ref != NULL)
	{
		while (begin_list)
		{
			if ((*cmp)(begin_list->data, data_ref) == 0)
				(*f)(begin_list->data);
			begin_list = begin_list->next;
		}
	}
}
