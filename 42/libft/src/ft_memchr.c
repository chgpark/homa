#include "../libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*tmps;
	unsigned int	ii;

	ii = 0;
	tmps = (unsigned char *)src;
	while (ii < n)
	{
		if (*tmps == c)
			return tmps;
		tmps++;
		ii++;
	}
	return NULL;
}
