#include "../libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int	n;
	char	tmpc;

	n = ft_strlen(src);
	tmpc = (char)c;
	while (n > -1)
	{
		if (src[n] == tmpc)
			return (char *)src + n;
		n--;
	}
	return NULL;
}
