/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 21:44:33 by cpark             #+#    #+#             */
/*   Updated: 2017/03/29 20:03:06 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_check_base(char *base, int i)
{
	int				b;
	char			*tmp;

	tmp = base;
	while (*base)
	{
		i = 0;
		while (base[i])
		{
			if (*base < '0' || (*base > '9' && *base < 'A') || *base > 'z'
					|| (*base > 'Z' && *base < 'a') || base[i + 1] == *base)
				return (0);
			i++;
		}
		base++;
	}
	b = 0;
	while (tmp[b])
		b++;
	if (b < 2)
		return (0);
	return (b);
}

char	*ft_check_nbr(char *nbr, char *from)
{
	int				i;
	int				j;
	char			*rt;

	while (*nbr && (*nbr == ' ' || *nbr == '\t' ||
				*nbr == '\n' || *nbr == '\v'))
		nbr++;
	rt = nbr;
	if (*nbr == '+' || *nbr == '-')
		nbr++;
	if (!*nbr)
		return (NULL);
	while (*nbr)
	{
		i = -1;
		j = 0;
		while (from[++i])
			j += (from[i] == *nbr ? 1 : 0);
		if (j != 1)
			*nbr = '\0';
		nbr++;
	}
	return (rt);
}

int		ft_convert_int(char *nbr, char *from, int *s, int b)
{
	int				i;
	unsigned int	rt;

	rt = (*nbr == from[0] ? 0 : 2147483649);
	*s = (*nbr == '-' ? -1 : 1);
	if (*nbr == '+' || *nbr == '-')
		nbr++;
	i = 0;
	while (from[++i])
	{
		if (*nbr == from[i])
			rt = 0;
	}
	while (*nbr)
	{
		i = -1;
		while (from[++i] && rt <= 2147483648)
		{
			if (*nbr == from[i])
				rt = rt * b + i;
		}
		nbr++;
	}
	return (rt);
}

char	*ft_convert_to(int nbr, char *base_to, int b, int count)
{
	char			*rt;
	int				i;

	count = count + (nbr < 0 ? 2 : 1);
	rt = malloc(count);
	rt[--count] = '\0';
	if (nbr < 0)
		rt[0] = '-';
	b = (nbr < 0 ? -b : b);
	while (count-- >= (b < 0 ? 2 : 1))
	{
		i = -1;
		while (base_to[++i])
		{
			if (i == (nbr < 0 ? -nbr : nbr) % b)
				rt[count] = base_to[i];
		}
		nbr = nbr / (nbr < 0 ? -b : b);
	}
	return (rt);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	unsigned int	cnv;
	unsigned int	tmp;
	int				b;
	int				s;
	int				count;

	b = ft_check_base(base_from, 0);
	nbr = ft_check_nbr(nbr, base_from);
	if (!nbr || !b || !*nbr)
		return (NULL);
	cnv = ft_convert_int(nbr, base_from, &s, b);
	if (cnv > (s < 0 ? 2147483648 : 2147483647))
		return (NULL);
	b = ft_check_base(base_to, 0);
	if (!b)
		return (NULL);
	count = (cnv == 0 ? 1 : 0);
	tmp = cnv;
	while (tmp)
	{
		tmp = tmp / b;
		count++;
	}
	return (ft_convert_to((int)(s * cnv), base_to, b, count));
}
