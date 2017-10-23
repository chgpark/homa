/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:17:13 by cpark             #+#    #+#             */
/*   Updated: 2017/03/20 10:29:02 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		ft_chk_base(char *b)
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

char	ft_chg_base(int digit, char *c)
{
	char	rt;

	rt = *(c + digit);
	return (rt);
}

void	ft_st(int n, int b, int ld, char *base)
{
	int		s;
	int		i;
	char	con[ld];

	s = 1;
	ld--;
	if (n < 0)
	{
		con[0] = '-';
		s = -1;
	}
	else
		ld--;
	con[ld--] = '\0';
	while (n != 0)
	{
		con[ld--] = ft_chg_base(n % b * s, base);
		n = n / b;
	}
	i = 0;
	while (con[i])
		ft_putchar(con[i++]);
	ft_putchar('\n');
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		b;
	int		l;
	int		tmp;

	tmp = nbr;
	l = 2;
	b = ft_chk_base(base);
	if (b == 0)
		return ;
	while (tmp != 0)
	{
		tmp = tmp / b;
		l++;
	}
	ft_st(nbr, b, l, base);
}
