/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:12:07 by cpark             #+#    #+#             */
/*   Updated: 2017/03/25 11:55:05 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *))
{
	t_btree	*tmp;

	tmp = *root;
	if (!tmp)
		*root = btree_create_node(item);
	else if ((*cmpf)(item, tmp->item) >= 0)
		btree_insert_data(&tmp->right, item, cmpf);
	else
		btree_insert_data(&tmp->left, item, cmpf);
}
