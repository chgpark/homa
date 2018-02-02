#include "../libft.h"

void	ft_bzero(void *src, size_t n)
{
	char	*tmp;

	tmp = (char *)src;
	while (n--)
	{
		*tmp = 0;
		tmp++;
	}
}
