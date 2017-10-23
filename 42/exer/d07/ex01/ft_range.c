/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:42:09 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 12:18:36 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int		*rt;
	int		*tmp;

	if (min >= max)
		return (NULL);
	if (!rt = malloc(sizeof(int) * (max - min)))
		return (NULL);
	tmp = rt;
	while (min < max)
		*tmp++ = min++;
	return (rt);
}
