/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <>                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 16:25:14 by cpark             #+#    #+#             */
/*   Updated: 2017/05/12 16:25:14 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <iostream>

void	ft_rc(char *str);
using namespace std;

int	main(int ac, char **av)
{
	char	str[100];
	//memset
	while (1)
{
	ft_rc(str);
	if (atoi(str) < 0)
{
	ft_putnbr(atoi(str));
	cout << endl << atoi(str) << endl;
}
}
	return 0;
}
