/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:36:40 by cpark             #+#    #+#             */
/*   Updated: 2017/03/13 20:20:21 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_find_next_prime(int nb)
{
	long n;

	n = 5;
	if (nb <= 1)
		return (2);
	if (nb <= 3)
		return (nb);
	if (nb % 2 == 0 || nb % 3 == 0)
		return (ft_find_next_prime(nb + 1));
	while (n * n <= nb)
	{
		if (nb % n == 0 || nb % (n + 2) == 0)
			return (ft_find_next_prime(nb + 1));
		n += 6;
	}
	return (nb);
}
