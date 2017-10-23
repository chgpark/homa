/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:43:13 by cpark             #+#    #+#             */
/*   Updated: 2017/03/22 17:04:21 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list		*ft_create_elem(void *data)
{
	t_list		*rt;

	rt = malloc(sizeof(t_list));
	if (rt)
	{
		rt->next = NULL;
		rt->data = data;
	}
	return (rt);
}
