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

void	ft_rc(char *str)
{
	unsigned int	i;

	i = rand() % 100;
	str[i] = 0;
	if (i)
	{
		while (--i >= 1)
			str[i] = rand() % 126 + 1;
		str[i] = rand() % 126 + 1;
	}
}
