#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	ii;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	ii = 0;
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (ii < n)
	{
		if (*tmps1 > *tmps2)
			return (int)(*tmps1 - *tmps2);
		else if (*tmps1 < *tmps2)
			return (int)(*tmps1 - *tmps2);
		tmps1++;
		tmps2++;
		ii++;
	}
	return 0;
}
