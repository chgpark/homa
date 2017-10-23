/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:18:27 by cpark             #+#    #+#             */
/*   Updated: 2017/03/23 13:44:43 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list		*ft_list_push_params(int ac, char **av)
{
	t_list	*list;
	t_list	*rt;

	if (ac > 0)
	{
		list = ft_create_elem(av[--ac]);
		rt = list;
		while (ac-- > 0)
		{
			list->next = ft_create_elem(av[ac]);
			list = list->next;
		}
		return (rt);
	}
	else
		return (NULL);
}
