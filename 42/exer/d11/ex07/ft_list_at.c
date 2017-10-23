/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:43:49 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 17:48:09 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list		*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	nbr = nbr + 1;
	if (begin_list && nbr != 0)
	{
		while (--nbr && begin_list->next)
			begin_list = begin_list->next;
		if (nbr != 0)
			return (0);
		else
			return (begin_list);
	}
	return (0);
}
