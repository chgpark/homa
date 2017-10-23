/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:09:31 by cpark             #+#    #+#             */
/*   Updated: 2017/03/22 10:01:56 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int		ft_list_size(t_list *begin_list)
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
