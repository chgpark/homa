/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:46:01 by cpark             #+#    #+#             */
/*   Updated: 2017/03/13 11:55:38 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_fibonacci(int index)
{
	int r;

	if (index < 0)
		return (-1);
	r = 0;
	if (index > 1)
		r = ft_fibonacci(index - 2) + ft_fibonacci(index - 1);
	else if (index == 1)
	{
		r = 1;
	}
	return (r);
}
