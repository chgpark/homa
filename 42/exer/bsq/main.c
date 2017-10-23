/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:58:34 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 17:55:31 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_create_inf(t_inf **inf)
{
	t_inf	*rt;

	*inf = malloc(sizeof(t_inf));
	rt = *inf;
	if (!rt)
	{
		*inf = NULL;
		return ;
	}
	rt->nl = 0;
	rt->nc = 0;
	rt->e = 0;
	rt->o = 0;
	rt->f = 0;
}

int		main(int ac, char **av)
{
	int			fd;
	int			**map;
	char		str[1];
	t_list_f	*lt_f;
	t_inf		*inf;
	int			i;

	lt_f = NULL;
	ft_create_inf(&inf);
	fd = open(av[1], O_RDONLY);
	while (read(fd, str, 1) > 0 && str[0] != '\n')
		ft_cr_lst_f(&lt_f, str[0]);
	ft_conv_inf(lt_f, inf);
	ft_list_clear_f(&lt_f);
	map = ft_insert_f(fd, 0, inf);
	i = 0;
	/*while (i < inf->nc)
	{
		printf("%d", map[0][i]);
		i++;
	}*/
	printf("%d\n", inf->nc);
	return (0);
}
