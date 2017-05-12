/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:34:57 by cpark             #+#    #+#             */
/*   Updated: 2017/05/12 15:34:57 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

using namespace std;

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	unsigned int	i;
	char		str[100];

	while (3)
	{
		i = rand() % 100;
		str[i] = 0;
		if (i)
		{
			while (--i >= 1)
				str[i] = rand() % 127;
			str[i] = rand() % 127;
		}
		ft_putstr(str);
	}
	return 0;
}
