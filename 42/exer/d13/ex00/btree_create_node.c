/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:05:55 by cpark             #+#    #+#             */
/*   Updated: 2017/03/24 00:02:39 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*rt;

	rt = malloc(sizeof(t_btree));
	if (rt)
	{
		rt->left = NULL;
		rt->right = NULL;
		rt->item = item;
	}
	return (rt);
}
