#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*r;

	n = ft_strlen(s);
	r = (char *)malloc(sizeof(char)*(n+1));
	if (r == NULL)
		return NULL;
	r[n] = 0;
	while (n--)
		r[n] = s[n];
	return r;
}
