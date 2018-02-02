#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmpd;
	char	*tmps;

	tmpd = (char *)dest;
	tmps = (char *)src;
	while (n--)
	{
		*tmpd = *tmps;
		tmpd++;
		tmps++;
	}
	return dest;
}
