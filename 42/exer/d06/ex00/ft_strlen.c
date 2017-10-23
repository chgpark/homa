/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 22:04:29 by cpark             #+#    #+#             */
/*   Updated: 2017/03/09 23:56:00 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	int a;
	int n;

	a = 0;
	n = *str;
	while (n > 0)
	{
		a++;
		n = *(str + a);
	}
	return (a);
}
