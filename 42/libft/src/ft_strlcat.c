#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dl, sl, ii;

	dl = ft_strlen(dest);
	sl = ft_strlen(src);
	ii = dl;
	while (ii < n)
	{
		dest[ii] = src[ii-dl];
		ii++;
	}
	dest[ii] = 0;
	return dl+sl;
}
