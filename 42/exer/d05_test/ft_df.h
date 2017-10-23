/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_df.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 09:08:24 by cpark             #+#    #+#             */
/*   Updated: 2017/03/24 09:14:02 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DF_H
 # define FT_DF_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putnbr_base(int nbr, char *base);
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

#endif
