/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 10:40:36 by cpark             #+#    #+#             */
/*   Updated: 2017/03/22 10:28:12 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int		ft_is_sort(int *tab, int length, int (*f)(int, int));

int		sort(int a, int b)
{
	if (a == b)
		return (0);
	else if (a > b)
		return (1);
	else
		return (-1);
}

int		main(void)
{
	int		tab[5];
	int		i;

	i = 5;
	while (i--)
		tab[i] = i;
	tab[3] = 0;
	printf("%d\n", ft_is_sort(tab, 5, &sort));
	return (0);
}
