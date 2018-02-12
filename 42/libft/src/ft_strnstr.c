#include "../libft.h"

char	*ft_strnstr(const char *havstack, const char *needle, size_t n)
{
	size_t	ii;
	size_t	nlen;

	nlen = ft_strlen(needle);
	while (*havstack && n-- > 0)
	{
		ii = 0;
		while (havstack[ii] && havstack[ii] == needle[ii])
			ii++;
		if (ii == nlen)
			return (char *)havstack;
		havstack++;
	}
	return NULL;
}
