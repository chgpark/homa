#include "../libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	while (n > 0 && *src)
	{
		*tmp = *src;
		tmp++;
		src++;
		n--;
	}
	if (*src == 0)
		while (n > 0)
		{
			*tmp = 0;
			tmp++;
			n--;
		}
	return dest;
}
