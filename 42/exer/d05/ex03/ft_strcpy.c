/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:05:35 by cpark             #+#    #+#             */
/*   Updated: 2017/03/20 10:22:45 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	char *tmp;

	tmp = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (tmp);
}
