/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:32:07 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 12:16:15 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	char	*rt;
	char	*tmp;

	i = 0;
	tmp = src;
	while (*tmp++)
		i++;
	if (!rt = malloc(sizeof(char) * (i + 1)))
		return (NULL);
	rt[i] = '\0';
	tmp = rt;
	while (*src)
		*tmp++ = *src++;
	return (rt);
}
