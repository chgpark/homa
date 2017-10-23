/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fila.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 12:59:42 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 13:50:38 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		ft_filba(t_list *lt_c, int c, int l, int n)
{
	t_list_l		*lt_l;

	lt_l = lt_c->data;
	if (lt_l && lt_l->data == '/' && lt_l->nb[0] == 1)
	{
		if (l == 1)
			return (ft_filbb(lt_c->next, c, l, n + 1));
		lt_l = lt_l->next;
		if (l == 2 || (lt_l && lt_l->data == '*' && lt_l->nb[0] == (l - 2)))
		{
			if (l != 2)
				lt_l = lt_l->next;
			if (lt_l && lt_l->data == '\\' && lt_l->nb[0] == 1)
				return (ft_filbb(lt_c->next, c, l, n + 1));
		}
	}
	return (0);
}

int		ft_filbb(t_list *lt_c, int c, int l, int n)
{
	t_list_l		*lt_l;

	if (c == 1)
		return (1);
	else if (c == n)
		return (ft_filbc(lt_c, l));
	lt_l = lt_c->data;
	if (lt_l && lt_l->data == '*')
	{
		if (l == 1)
			return (ft_filbb(lt_c->next, c, l, n + 1));
		else if (l == 2 && lt_l->data == '*' && lt_l->nb[0] == 2)
			return (ft_filbb(lt_c->next, c, l, n + 1));
		lt_l = lt_l->next;
		if (lt_l && lt_l->data == ' ' && lt_l->nb[0] == (l - 2))
		{
			lt_l = lt_l->next;
			if (lt_l && lt_l->data == '*' && lt_l->nb[0] == 1)
				return (ft_filbb(lt_c->next, c, l, n + 1));
		}
	}
	return (0);
}

int		ft_filbc(t_list *lt_c, int l)
{
	t_list_l		*lt_l;

	lt_l = lt_c->data;
	if (lt_l && lt_l->data == '\\')
	{
		if (l == 1)
			return (1);
		lt_l = lt_l->next;
		if (l == 2 || (lt_l && lt_l->data == '*' && lt_l->nb[0] == (l - 2)))
		{
			if (l != 2)
				lt_l = lt_l->next;
			if (lt_l && lt_l->data == '/' && lt_l->nb[0] == 1)
				return (1);
		}
	}
	return (0);
}
