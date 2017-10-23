/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:20:30 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 10:43:24 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	if (data_ref != NULL)
	{
		while (begin_list)
		{
			if ((*cmp)(begin_list->data, data_ref) == 0)
				return (begin_list);
			begin_list = begin_list->next;
		}
	}
	return (begin_list);
}
