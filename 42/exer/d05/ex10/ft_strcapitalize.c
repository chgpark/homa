/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 18:46:04 by cpark             #+#    #+#             */
/*   Updated: 2017/03/15 16:18:46 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		find_up(char *str)
{
	if (*str >= 'A' && *str <= 'Z')
		return (1);
	else if (*str >= '0' && *str <= '9')
		return (1);
	return (0);
}

char	*chg_lo(char *str)
{
	while (*str >= 'A' && *str <= 'Z')
	{
		*str = *str + 32;
		str++;
	}
	return (str);
}

char	*ft_strcapitalize(char *str)
{
	char *tmp;

	tmp = str;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		str++;
	}
	str = tmp;
	while (*str != '\0')
	{
		if (find_up(str++))
			str = chg_lo(str);
	}
	return (tmp);
}
