#include "../libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	cl;
	size_t	ii;

	ii = 0;
	cl = ft_strlen(dest);
	while (ii < n && src[ii])
	{
		dest[cl+ii] = src[ii];
		ii++;
	}
	dest[cl+ii] = 0;
	return dest;
}
