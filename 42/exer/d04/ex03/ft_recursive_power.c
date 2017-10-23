/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:34:01 by cpark             #+#    #+#             */
/*   Updated: 2017/03/13 11:57:33 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_recursive_power(int nb, int power)
{
	int r;

	r = 1;
	if (power < 0)
		return (0);
	if (power >= 1)
		r = nb * ft_recursive_power(nb, power - 1);
	return (r);
}
