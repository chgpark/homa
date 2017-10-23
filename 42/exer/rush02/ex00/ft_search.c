/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 23:22:32 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 14:42:20 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		ft_chknbr(t_list *lt_c, int l)
{
	int			i;
	t_list_l	*lt_l;

	i = 0;
	while (lt_c)
	{
		lt_l = lt_c->data;
		if (l != ft_list_size_l(lt_l))
			return (1);
		lt_c = lt_c->next;
	}
	return (0);
}

void	ft_search(t_list *lt_c, int c, int l)
{
	if (ft_chknbr(lt_c, l))
		ft_print(1, -1, -1);
	else if (ft_filaa(lt_c, c, l, 1))
		ft_print(0, l, c);
	else if (ft_filba(lt_c, c, l, 1))
		ft_print(1, l, c);
	else if (ft_filca(lt_c, c, l, 1))
		ft_print(2, l, c);
	else if (ft_filda(lt_c, c, l, 1))
		ft_print(3, l, c);
	else if (ft_filea(lt_c, c, l, 1))
		ft_print(4, l, c);
	else
		ft_print(1, -1, -1);
}

int		ft_chk(t_list *lt_c)
{
	int			c;
	int			l;

	if (lt_c)
	{
		c = ft_list_size_c(lt_c);
		l = ft_list_size_l(lt_c->data);
		ft_search(lt_c, c, l);
		return (0);
	}
	else
	{
		ft_print(1, -1, -1);
		return (-1);
	}
}
