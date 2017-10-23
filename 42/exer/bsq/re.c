/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:35:29 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 17:54:51 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int		**ft_insert_f(int fd, int nc, t_inf *inf)
{
	char			str[1];
	unsigned int	nb[1000];
	int				i;
	int				j;

	i = -1;
	j = 1;
	while (read(fd, str, 1) > 0 && str[0] != '\n')
	{
		if (!(nc % 32))
			i++;
		if (str[0] == inf->o)
			nb[i] = nb[i] + j;
		j = j * 2;
		nc += 1;
	}
	inf->nc = nc;
	return (ft_conv_f(nb, inf));
}
