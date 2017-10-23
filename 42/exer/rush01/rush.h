/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 14:22:51 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 18:10:00 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

# include <stdlib.h>
# include <unistd.h>
# define RC *(*(c + row) + col)

void	ft_putchar(char c);
void	ft_putnbr(int nbr[9][9]);
void	ft_putstr(char *str);
int		ft_errchk(int i, char **c);
int		ft_filter(int input, int line, int n[81], int a);
void	ft_chrtonbr(char **c, int nbr[9][9]);
int		ft_sdk_rc(int line[81], int l, int i);
int		ft_sdk_line(int line[81], int l);
void	ft_sdk(int nbr[9][9], int i);
void	ft_count(int nbr[9][9], int i, int *count);
int		ft_sdk_count(int line[81], int l, int *count);
int		ft_sdk_rc_count(int line[81], int l, int i, int *count);

#endif
