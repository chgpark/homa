/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:54:31 by cpark             #+#    #+#             */
/*   Updated: 2017/03/24 15:58:26 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fowc.h"

void	ft_err(char *str)
{
	int		count;

	count = 0;
	while (str[count])
		count++;
	write(errno, "ft_cat: ", 8);
	write(errno, str, count);
	write(errno, ": No such file or directory\n", 28);
}
