/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:00:12 by cpark             #+#    #+#             */
/*   Updated: 2017/03/11 11:37:50 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

int		ft_count(int n)
{
	int a;
	int i;

	a = 1;
	i = 0;
	while (i < n)
	{
		a = a * (10 - i);
		i++;
	}
	while (i > 0)
	{
		a = a / i;
		i--
	}
	return (a);
}

void	pt_int(int *p, int n)
{
	int i;

	i = 0;
	while (i <= n)
	{
		*p++ = i;
		i++;
	}
}
	{
		ft_putchar(*p + '0');
		p++;
	}
	if (n != 0)
	{
		ft_putchar(',');
		ft_putchar(' ');
	}
}

void	ft_print_combn(int n)
{
	int count;
	int a[n];

	count = ft_count(n);
	pt_int(a, n);
	
