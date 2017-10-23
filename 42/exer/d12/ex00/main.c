/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:56:39 by cpark             #+#    #+#             */
/*   Updated: 2017/03/24 14:32:16 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fowc.h"

int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE + 1];

	if (ft_err(argc))
		return (1);
	fd = open(argv[1], O_RDONLY, S_IRUSR);
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	write(1, buf, ret);
	close(fd);
	return(0);
}
