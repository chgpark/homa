#include "../libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	char	*t;

	t = (char *)src;
	while (n-- > 0)
	{
		*t = c;
		t++;
	}
	return src;
}

