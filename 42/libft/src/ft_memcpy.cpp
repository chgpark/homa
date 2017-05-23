/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 10:04:26 by cpark             #+#    #+#             */
/*   Updated: 2017/05/19 10:04:26 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;
	char	*tmp_a;
	char	*tmp_b;
	void	*tmp;

	i = -1;
	tmp = dst;
	tmp_b = (char *) src;
	while (++i < n)
	{
		tmp_a = (char *) (tmp + i);
		*tmp_a = tmp_b[i];
	}
	return dst;
}
