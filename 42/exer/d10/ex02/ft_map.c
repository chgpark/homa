/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:58:58 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 10:05:36 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_map(int *tab, int length, int (*f)(int))
{
	int		*rt;
	int		i;

	i = -1;
	rt = malloc(sizeof(int) * length);
	while (++i <= length - 1)
		rt[i] = f(tab[i]);
	return (rt);
}
