/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 08:52:51 by cpark             #+#    #+#             */
/*   Updated: 2017/03/28 12:30:12 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_concat_params(int argc, char **argv)
{
	char	*rt;
	char	*tmp_c;
	int		tmp_i;
	int		i;

	i = 0;
	tmp_i = argc;
	while (--tmp_i)
	{
		tmp_c = argv[tmp_i];
		while (tmp_c++)
			i++;
	}
	if (!rt = malloc(sizeof(char) * (i + argc - 1)))
		return (NULL);
	tmp_c = rt;
	i = 0;
	while (++i < argc)
	{
		while (*argv[i])
			*tmp_c++ = *argv[i]++;
		if (i < argc - 1)
			*tmp_c++ = '\n';
	}
	*tmp_c = '\0';
	return (rt);
}
