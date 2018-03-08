#include "../libft.h"

char	*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	char	*rt;

	rt = (char *)malloc(sizeof(char) * (len+1));
	if (rt == NULL)
		return NULL;
	ft_strncpy(rt, s1+start, len);
	rt[len] = '\0';
	return rt;
}
