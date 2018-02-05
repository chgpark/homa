#include "../libft.h"

char *ft_strcat(char *dest, const char *src)
{
	size_t	n;
	size_t	ii;

	ii = 0;
	n = ft_strlen(dest);
	while (src[ii])
	{
		dest[n+ii] = src[ii];
		ii++;
	}
	dest[n+ii] = 0;
	return dest;
}
