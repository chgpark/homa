/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 13:22:19 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 15:40:06 by maechard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rush.h"

int		main(void)
{
	int			*nb;
	char		str[1];
	char		c;
	t_list_l	*lt_l;
	t_list		*lt_c;

	while (read(0, str, 1))
	{
		if (c != str[0] && str[0] != '\n')
		{
			if (!(nb = malloc(sizeof(int))))
				return (0);
			c = str[0];
			ft_cr_lst_l(&lt_l, c, nb);
		}
		if (str[0] != '\n')
			*nb += 1;
		if (str[0] == '\n')
		{
			ft_cr_lst(&lt_c, lt_l);
			lt_l = NULL;
			c = 0;
		}
	}
	return (ft_chk(lt_c));
}
