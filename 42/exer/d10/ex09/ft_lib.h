/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doop.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 16:51:59 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 17:54:21 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOOP_H
# define FT_DOOP_H

# include <unistd.h>
# define AT(x) ft_atoi(x)
# define CHK(x, y, z) ft_chkcal(x, y, z)

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
int		ft_add(int a, int b);
int		ft_sub(int a, int b);
int		ft_mul(int a, int b);
int		ft_div(int a, int b);
int		ft_mod(int a, int b);
int		ft_usage(int a, int b);
int		ft_atoi(char *str);

typedef	struct	s_opp
{
	char	*str;
	int		(*ft)(int, int);
}				t_opp;

#endif
