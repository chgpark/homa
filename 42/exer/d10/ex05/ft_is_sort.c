/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 10:30:15 by cpark             #+#    #+#             */
/*   Updated: 2017/03/22 10:29:35 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	if (length > 1)
	{
		if (ft_is_sort(tab, length - 1, f))
			return (f(tab[length], tab[length - 1]) < 0 ? 0 : 1);
		return (0);
	}
	else
		return (f(tab[length], tab[length - 1]) < 0 ? 0 : 1);
}
