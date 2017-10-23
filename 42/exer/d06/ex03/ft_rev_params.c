/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:14:11 by cpark             #+#    #+#             */
/*   Updated: 2017/03/15 18:18:59 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		main(int argc, char **argv)
{
	while (--argc)
	{
		while (*argv[argc])
		{
			ft_putchar(*argv[argc]);
			argv[argc]++;
		}
		ft_putchar('\n');
	}
	return (0);
}
