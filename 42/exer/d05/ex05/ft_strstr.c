/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:33:07 by cpark             #+#    #+#             */
/*   Updated: 2017/03/15 14:56:14 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		srch(char *str, char *to_find)
{
	while (*to_find != '\0')
	{
		if (*str++ != *to_find++)
			return (0);
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	if (*to_find == '\0')
		return (str);
	while (*str != '\0')
	{
		if (*str == *to_find && srch(str, to_find))
			return (str);
		str++;
	}
	return (0);
}
