/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eight_queens_puzzle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:38:13 by cpark             #+#    #+#             */
/*   Updated: 2017/03/13 11:12:36 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		filter_1(int n, int i, int *c)
{
	int ct;

	ct = 0;
	while (ct < n)
	{
		if (c[ct] == i)
		{
			return (0);
		}
		ct++;
	}
	return (1);
}

int		filter_2(int n, int i, int *c)
{
	int ct;

	ct = 1;
	while (ct < n + 1)
	{
		if ((c[n - ct] > 0) && (c[n - ct] == i + ct || c[n - ct] == i - ct))
			return (0);
		ct++;
	}
	return (1);
}

int		chk_rc(int n, int *c)
{
	int rt;
	int i;

	i = 1;
	rt = 0;
	if (n == 8)
		return (1);
	while (i < 9)
	{
		c[n] = 0;
		if (filter_1(n, i, c) && filter_2(n, i, c))
		{
			c[n] = i;
			rt = rt + chk_rc(n + 1, c);
		}
		i++;
	}
	return (rt);
}

int		ft_eight_queens_puzzle(void)
{
	int c[8];
	int rt;
	int i;

	i = 1;
	rt = 0;
	while (i < 9)
	{
		c[0] = i++;
		rt = rt + chk_rc(1, c);
	}
	return (rt);
}
