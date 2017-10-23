/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:51:32 by cpark             #+#    #+#             */
/*   Updated: 2017/03/15 18:05:57 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		ft_count(int n)
{
	int a;
	int i;

	i = 1;
	a = 1;
	while (a != 0)
	{
		a = n / (i * 10);
		i = i * 10;
	}
	return (i);
}

void	ft_print(int a, int b)
{
	while (b > 1)
	{
		ft_putchar(a / (b / 10) + '0');
		a = a % (b / 10);
		b = b / 10;
	}
}

void	ft_putnbr(int nb)
{
	int i;
	int r;

	r = nb % 10;
	nb = nb / 10;
	i = ft_count(nb);
	if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
		r = r * -1;
	}
	ft_print(nb, i);
	if (nb > 0)
	{
		ft_putchar(r + '0');
	}
}
