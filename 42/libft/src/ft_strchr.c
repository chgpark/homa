#include "../libft.h"

char	*ft_strchr(const char *src, int c)
{
	char	*tmp;
	char	cc;

	cc = c;
	tmp = (char *)src;
	while (*tmp)
	{
		if (*tmp == cc)
			return tmp;
		tmp++;
	}
	if (*tmp == cc)
		return tmp;
	else
		return NULL;
}
