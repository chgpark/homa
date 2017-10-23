/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:35:17 by cpark             #+#    #+#             */
/*   Updated: 2017/03/29 15:40:55 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

int		main(int ac, char **av)
{
	if (ac != 4)
		return (0);
	printf("%s\n", ft_convert_base(av[1], av[2], av[3]));
	return (0);
}
