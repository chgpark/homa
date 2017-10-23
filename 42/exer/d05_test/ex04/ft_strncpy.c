/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:29:16 by cpark             #+#    #+#             */
/*   Updated: 2017/03/21 08:37:06 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char			*s;
	char			*rt;
	unsigned int	i;

	i = 1;
	while (src[i])
		i++;
	s = dest;
	rt = src;
	while (n > 0 && *rt != '\0')
	{
		*s++ = *rt++;
		--n;
	}
	while (n > 0)
	{
		*s++ = '\0';
		--n;
	}
	if (i >= n)
		return (dest);
	else
		return (src);
}
