/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 08:23:40 by cpark             #+#    #+#             */
/*   Updated: 2017/05/29 08:23:43 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int		i;
	char		*tmp_a;
	char		buf[n];
	const char	*tmp_b;

	i = -1;
	tmp_a = (char *) dst;
	tmp_b = (const char *) src;
	while (++i < n)
		buf[i] = *tmp_b++;
	i = -1;
	while (++i < n)
		*tmp_a++ = buf[i];
	return dst;
}
