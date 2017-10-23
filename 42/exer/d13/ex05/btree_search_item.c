/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:55:39 by cpark             #+#    #+#             */
/*   Updated: 2017/03/25 11:55:22 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	int		i;

	if (root)
	{
		i = (*cmpf)(root->item, data_ref);
		if (i > 0)
			return (btree_search_item(root->left, data_ref, cmpf));
		if (!i)
			return (root->item);
		else
			return (btree_search_item(root->right, data_ref, cmpf));
	}
	else
		return (NULL);
}
