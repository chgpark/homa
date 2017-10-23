/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:51:44 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 10:06:58 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*chga;
	t_list	*chgb;

	tmp = *begin_list;
	if (tmp && tmp->next)
	{
		chga = tmp->next;
		tmp->next = NULL;
		chgb = *begin_list;
		*begin_list = chga;
		while (*begin_list)
		{
			tmp = *begin_list;
			chga = tmp->next;
			tmp->next = chgb;
			chgb = *begin_list;
			*begin_list = chga;
		}
		*begin_list = chgb;
	}
}
