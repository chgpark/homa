/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:19:43 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 19:49:45 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

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

void	ft_sort(int size, char **str)
{
	int		i_1;
	int		i_2;
	char	*s;

	i_1 = 1;
	while (i_1 <= size)
	{
		i_2 = 1;
		while (i_2 <= size - i_1)
		{
			if (ft_strcmp(str[i_2], str[i_2 + 1]) > 0)
			{
				s = str[i_2];
				str[i_2] = str[i_2 + 1];
				str[i_2 + 1] = s;
			}
			i_2++;
		}
		i_1++;
	}
}

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	ft_sort(argc - 1, argv);
	while (i <= argc - 1)
	{
		ft_putstr(argv[i++]);
		ft_putchar('\n');
	}
	return (0);
}
