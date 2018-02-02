#include "../libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*tmpd;
	char	*tmps;

	tmpd = (char *) dest;
	tmps = (char *)src;
	while (n--)
	{
		*tmpd = *tmps;
		tmpd++;
		if (*tmps == (char)c)
			return (void *)tmpd;
		tmps++;
	}
	return NULL;
}
