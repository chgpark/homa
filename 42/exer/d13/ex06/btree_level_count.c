/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 19:29:18 by cpark             #+#    #+#             */
/*   Updated: 2017/03/24 01:22:01 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int		btree_level_count(t_btree *root)
{
	int		rtl;
	int		rtr;

	if (!root)
		return (0);
	rtl = btree_level_count(root->left);
	rtr = btree_level_count(root->right);
	if (rtl > rtr)
		return (1 + rtl);
	else
		return (1 + rtr);
}
