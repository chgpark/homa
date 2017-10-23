/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:35:48 by cpark             #+#    #+#             */
/*   Updated: 2017/03/22 21:49:16 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_clear(t_list **begin_list)
{
	t_list	*tmp;
	void	*chg;

	while (*begin_list)
	{
		tmp = *begin_list;
		tmp->data = NULL;
		chg = tmp->next;
		tmp->next = NULL;
		free(tmp);
		*begin_list = chg;
	}
}
