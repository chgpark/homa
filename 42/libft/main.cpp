/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <>                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 16:25:14 by cpark             #+#    #+#             */
/*   Updated: 2017/05/17 11:26:59 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/libft.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

#define a
void	ft_rc(char *str);
using namespace std;

int	main(int ac, char **av)
{
	char	*pch;
	char	str[] = "Example string";
	pch = (char *) ft_memchr(str, 1, strlen(str));
	printf("%d\n", pch);
	printf("%d\n", pch - str + 1);
/*
	char	str[100];
	char	st[40];
	int	i = 0;
#ifdef a
	while (++i < 100)
	{
		ft_rc(str);
		cout << sizeof(st) << endl;
		ft_memmove(st, str, 30);//rand() % (strlen(str) + 1));
//		ft_putendl(st);
		cout << sizeof(st) << endl;
		cout << str << endl;
		cout << st << endl;// << st << endl;
	}
#endif
*/
	return 0;
}
