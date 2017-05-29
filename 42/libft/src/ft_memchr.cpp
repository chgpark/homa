/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 09:12:29 by cpark             #+#    #+#             */
/*   Updated: 2017/05/29 09:12:29 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *ptr, int value, size_t n)
{
	char	*tmp;

	tmp = (char *) ptr;
	while (n-- > 0)
		if ((int) *tmp == value)
			return tmp;
		else
			tmp++;
	return 0;
}
