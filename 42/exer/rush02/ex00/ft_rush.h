/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rush.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 13:20:55 by cpark             #+#    #+#             */
/*   Updated: 2017/03/26 14:34:19 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RUSH_H
# define FT_RUSH_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;
typedef struct		s_list_l
{
	struct s_list_l	*next;
	int				*nb;
	char			data;
}					t_list_l;

void				ft_cr_lst(t_list **begin_list, void *data);
void				ft_list_clear(t_list **begin_list);
int					ft_list_size_c(t_list *begin_list);
void				ft_cr_lst_l(t_list_l **begin_list, char data, int *nb);
void				ft_list_clear_l(t_list_l **begin_list);
int					ft_list_size_l(t_list_l *begin_list);
void				ft_print(int n, int r, int c);
int					ft_filaa(t_list *lt_c, int c, int l, int n);
int					ft_filab(t_list *lt_c, int c, int l, int n);
int					ft_filac(t_list *lt_c, int l);
int					ft_filba(t_list *lt_c, int c, int l, int n);
int					ft_filbb(t_list *lt_c, int c, int l, int n);
int					ft_filbc(t_list *lt_c, int l);
int					ft_filca(t_list *lt_c, int c, int l, int n);
int					ft_filcb(t_list *lt_c, int c, int l, int n);
int					ft_filcc(t_list *lt_c, int l);
int					ft_filda(t_list *lt_c, int c, int l, int n);
int					ft_fildb(t_list *lt_c, int c, int l, int n);
int					ft_fildc(t_list *lt_c, int l);
int					ft_filea(t_list *lt_c, int c, int l, int n);
int					ft_fileb(t_list *lt_c, int c, int l, int n);
int					ft_filec(t_list *lt_c, int l);
int					ft_chk(t_list *lt_c);

#endif
