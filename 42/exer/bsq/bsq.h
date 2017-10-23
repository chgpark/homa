/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:17:48 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 17:38:13 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
 # define BSQ_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_list_f
{
	struct s_list_f	*next;
	char			data;
}					t_list_f;
typedef struct		s_inf
{
	int				nl;
	int				nc;
	char			e;
	char			o;
	char			f;
}					t_inf;
void				ft_cr_lst_f(t_list_f **begn_list, char data);
void				ft_list_clear_f(t_list_f **begin_list);
int					ft_list_size_f(t_list_f *begin_list);
t_list_f			*ft_create_elem_f(char data);
char				*ft_chgn(t_list_f *begin_list, int n);
void				ft_conv_inf(t_list_f *lt_f, t_inf *inf);
int					**ft_conv_f(unsigned int *nb, t_inf *inf);
int					**ft_insert_f(int fd, int nc, t_inf *inf);

#endif
