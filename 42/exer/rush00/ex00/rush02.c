/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:33:00 by bmickael          #+#    #+#             */
/*   Updated: 2017/03/11 17:24:12 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	line_1(int a)
{
	int i;

	ft_putchar('A');
	i = 0;
	while (i++ < (a - 2))
		ft_putchar('B');
	if (a > 1)
		ft_putchar('A');
	ft_putchar('\n');
}

void	others_lines(int a, int b)
{
	int i;

	b -= 2;
	while (b > 0)
	{
		ft_putchar('B');
		i = 0;
		while (i++ < (a - 2))
			ft_putchar(' ');
		if (a > 1)
			ft_putchar('B');
		b--;
		ft_putchar('\n');
	}
}

void	line_2(int a, int b)
{
	int i;

	if (b == 1)
		return ;
	ft_putchar('C');
	i = 0;
	while (i++ < (a - 2))
		ft_putchar('B');
	if (a > 1)
		ft_putchar('C');
	ft_putchar('\n');
}

void	rush(int x, int y)
{
	if (x < 1 || y < 1)
		return ;
	line_1(x);
	others_lines(x, y);
	line_2(x, y);
}
