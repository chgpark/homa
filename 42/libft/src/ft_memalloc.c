#include "../libft.h"

void	*ft_memalloc(size_t size)
{
	void	*r;

	r = (void *)malloc(sizeof(char) * size);
	if (r == NULL)
		return NULL;
	ft_memset(r, 0, size);
	return r;
}
