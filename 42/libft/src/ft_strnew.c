#include "../libft.h"

char	*ft_strnew(size_t size)
{
	char	*rt;

	rt = (char *)malloc(sizeof(char) * (size+1));
	if (rt == NULL)
		return NULL;
	ft_memset(rt, 0, size+1);
	return rt;
}
