/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:54:39 by ale-baux          #+#    #+#             */
/*   Updated: 2017/03/11 18:58:59 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	print_line(int n, char first_c, char second_c, char third_c)
{
	int i;

	i = 1;
	while (i <= n)
	{
		if (i == 1)
			ft_putchar(first_c);
		else if (i == n)
			ft_putchar(third_c);
		else
		{
			ft_putchar(second_c);
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
			print_line(x, 'A', 'B', 'C');
		else if (i == y)
			print_line(x, 'A', 'B', 'C');
		else
		{
			print_line(x, 'B', ' ', 'B');
		}
		i++;
	}
}
