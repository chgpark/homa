#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*tmps;

	tmps = (void *)malloc(sizeof(char)*n);
	if (tmps == NULL)
		return dest;
	ft_memcpy(tmps, src, n);
	ft_memcpy(dest, tmps, n);
	free(tmps);
	return dest;
}
