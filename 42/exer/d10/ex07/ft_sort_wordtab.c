/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_wordtab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:00:30 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 16:19:53 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	ft_sort_wordtab(char **tab)
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
			if (ft_strcmp(tab[i_2], tab[i_2 + 1]) > 0)
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

