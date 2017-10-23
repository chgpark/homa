/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 02:14:12 by cpark             #+#    #+#             */
/*   Updated: 2017/03/11 18:20:07 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rt_print(int n)
{
	int i;

	i = 1;
	while (i <= n)
	{
		if (i == 1)
			ft_putchar('/');
		else if (i == n)
			ft_putchar('\\');
		else
		{
			ft_putchar('*');
		}
		i++;
	}
	ft_putchar('\n');
}

void	rm_print(int n)
{
	int i;

	i = 1;
	while (i <= n)
	{
		if (i == 1)
			ft_putchar('*');
		else if (i == n)
			ft_putchar('*');
		else
		{
			ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
}

void	rb_print(int n)
{
	int i;

	i = 1;
	while (i <= n)
	{
		if (i == 1)
			ft_putchar('\\');
		else if (i == n)
			ft_putchar('/');
		else
		{
			ft_putchar('*');
		}
		i++;
	}
	ft_putchar('\n');
}

void	rush(int x, int y)
{
	int i;

	if (x < 1 || y < 1)
		return ;
	i = 1;
	while (i <= y)
	{
		if (i == 1)
			rt_print(x);
		else if (i == y)
			rb_print(x);
		else
		{
			rm_print(x);
		}
		i++;
	}
}
