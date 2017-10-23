/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:26:55 by cpark             #+#    #+#             */
/*   Updated: 2017/03/20 20:35:01 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_par.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	struct	s_stock_par		*r;

	r = ft_param_to_tab(argc, argv);
	ft_show_tab(r);
	return (0);
}
