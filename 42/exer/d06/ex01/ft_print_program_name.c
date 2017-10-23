/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:51:51 by cpark             #+#    #+#             */
/*   Updated: 2017/03/19 15:05:54 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		main(int argc, char **argv)
{
	argc = 0;
	while (*argv[argc])
	{
		ft_putchar(*argv[argc]);
		argv[argc]++;
	}
	ft_putchar('\n');
	return (0);
}
