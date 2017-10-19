/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_wordtab.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 16:16:41 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 16:22:01 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_advanced_sort_wordtab(char **tab, int(*cmp)(char *, char *))
{
	int		i_1;
	int		i_2;
	int		size;
	char	*s;

	size = 0;
	while (tab[size])
		size++;
	i_1 = 0;
	while (i_1 <= size - 1)
	{
		i_2 = 0;
		while (i_2 <= size - i_1 - 1)
		{
			if (cmp(tab[i_2], tab[i_2 + 1]) > 0)
			{
				s = tab[i_2];
				tab[i_2] = tab[i_2 + 1];
				tab[i_2 + 1] = s;
			}
			i_2++;
		}
		i_1++;
	}
}
