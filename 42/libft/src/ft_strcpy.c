#include "../libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*tmp;

	tmp = dest;
	while (*src)
	{
		*tmp = *src;
		tmp++;
		src++;
	}
	*tmp = 0;
	return dest;
}
