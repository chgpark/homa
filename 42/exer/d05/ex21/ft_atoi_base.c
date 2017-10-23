/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 09:56:23 by cpark             #+#    #+#             */
/*   Updated: 2017/03/20 11:43:10 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		ft_chk_abase(char *b)
{
	int		i;
	int		i_tmp;
	int		rt;

	i = 0;
	while (b[i])
		i++;
	rt = i;
	while (i)
	{
		i_tmp = 0;
		while (i_tmp < i - 1)
		{
			if (b[i - 1] < 48 || (b[i - 1] > 57 && b[i - 1] < 65))
				return (0);
			else if ((b[i - 1] > 90 && b[i - 1] < 97) || b[i - 1] > 122)
				return (0);
			else if (b[i - 1] == b[i_tmp++])
				return (0);
		}
		i--;
	}
	return (rt);
}

int		ft_chk(char nbr, char *base)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (base[i])
	{
		if (nbr == base[i])
			l++;
		i++;
	}
	if (l)
		return (1);
	else
		return (0);
}

int		ft_chk_nbr(char *str, char *base, int b)
{
	int		i;
	int		rt;
	int		a;

	rt = 0;
	while (ft_chk(*str, base))
	{
		i = 0;
		a = 0;
		while (base[i])
		{
			if (*str == base[i])
			{
				rt = rt * b + i;
				a++;
			}
			i++;
		}
		if (a < 0)
			return (rt);
		str++;
	}
	return (rt);
}

int		ft_atoi_base(char *str, char *base)
{
	int		b;
	int		s;

	s = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '-')
	{
		s = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	b = ft_chk_abase(base);
	if (b == 0)
		return (b);
	else
		return (ft_chk_nbr(str, base, b) * s);
}
