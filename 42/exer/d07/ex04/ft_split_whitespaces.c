/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 09:12:52 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 14:11:44 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_chk_str(char *tmp)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '\n')
		{
			i++;
			count++;
			while (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '\n' && tmp[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

int		ft_chk_wrd(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '\n' && tmp[i])
		i++;
	return (i);
}

char	**ft_split_whitespaces(char *str)
{
	int		i_str;
	int		i;
	char	**rt;

	i = 0;
	i_str = ft_chk_str(str);
	if (!rt = malloc(sizeof(char *) * (i_str + 1)))
		return (NULL);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str)
		{
			if (!rt[i] = malloc(sizeof(char) * (ft_chk_wrd(str) + 1)))
				return (NULL);
			i_str = 0;
			while (*str != ' ' && *str != '\t' && *str != '\n' && *str)
				rt[i][i_str++] = *str++;
			rt[i][i_str] = '\0';
			i++;
		}
		else
			str++;
	}
	rt[i] = 0;
	return (rt);
}
