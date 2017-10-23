/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do-op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:17:09 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 18:01:53 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lib.h"
#include "ft_opp.h"

int		ft_calcul(int a, char st, int b)
{
	if (st == g_opptab[1].str[0])
		ft_putnbr(g_opptab[1].ft(a, b));
	else if (st == g_opptab[0].str[0])
		ft_putnbr(g_opptab[0].ft(a, b));
	else if (st == g_opptab[2].str[0])
		ft_putnbr(g_opptab[2].ft(a, b));
	else if (st == g_opptab[3].str[0])
	{
		if (b == 0)
			return (1);
		ft_putnbr(g_opptab[3].ft(a, b));
	}
	else
	{
		if (b == 0)
			return (2);
		ft_putnbr(g_opptab[4].ft(a, b));
	}
	return (0);
}

int		ft_chkcal(int a, char *s, int b)
{
	int		i;
	int		j;
	char	st;

	j = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '+' || s[i] == '-'
				|| s[i] == '/' || s[i] == '%' || s[i] == '*')
		{
			st = s[i];
			j++;
		}
		else
			return (3);
	}
	if (j != 1)
		return (3);
	else
		return (ft_calcul(a, st, b));
}

int		main(int argc, char **argv)
{
	if (argc != 4)
		return (0);
	argc = CHK(AT(argv[1]), argv[2], AT(argv[3]));
	if (argc == 1)
		ft_putstr("Stop : division by zero");
	else if (argc == 2)
		ft_putstr("Stop : modulo by zero");
	else if (argc == 3)
		ft_putstr("error : only [ - + * / % ] are accepted.");
	ft_putchar('\n');
	return (0);
}
