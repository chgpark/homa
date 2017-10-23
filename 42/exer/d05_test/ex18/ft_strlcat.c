/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 09:28:48 by cpark             #+#    #+#             */
/*   Updated: 2017/03/15 15:01:58 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char			*ft_strncat_len(char *dest, char *src, int nb)
{
	char	*tmp;

	tmp = dest;
	while (*dest && nb)
	{
		dest++;
		nb--;
	}
	if (*dest != 0)
		return (tmp);
	else
	{
		while (*src && nb--)
			*dest++ = *src++;
		*dest = '\0';
		return (tmp);
	}
}

unsigned int	ft_strlen_cat(char *dest, char *src, int nb)
{
	unsigned int	i_dest;
	unsigned int	i_src;

	i_dest = 0;
	i_src = 0;
	while (*dest++ && nb--)
		i_dest++;
	while (*src++)
		i_src++;
	return (i_dest + i_src);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = ft_strlen_cat(dest, src, size);
	dest = ft_strncat_len(dest, src, size - 1);
	return (i);
}
