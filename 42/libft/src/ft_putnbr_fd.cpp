/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 10:58:39 by cpark             #+#    #+#             */
/*   Updated: 2017/05/17 10:58:39 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		if (n < -9)
			ft_putnbr(n / -10);
		c =  -(n % 10) + '0';
		write(fd, &c, 1);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}
