/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:52:36 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 17:54:42 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lib.h"

int		del_spa(char *str)
{
	int i;

	i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
	{
		i++;
		str++;
	}
	return (i);
}

int		chk_sign(char *str, int *s)
{
	int i;

	i = 0;
	if (*str == '-')
	{
		*s = -1;
		i++;
	}
	else if (*str == '+')
	{
		i++;
	}
	return (i);
}

int		ft_atoi(char *str)
{
	int		s;
	int		rt;

	rt = 0;
	s = 1;
	str = str + del_spa(str);
	str = str + chk_sign(str, &s);
	while (*str >= 48 && *str <= 57)
	{
		rt = rt * 10 + *str++ - 48;
	}
	return (rt * s);
}
