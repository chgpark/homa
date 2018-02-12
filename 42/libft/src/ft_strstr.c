#include "../libft.h"

char	*ft_strstr(const char *havstack, const char *needle)
{
	size_t		ii;
	size_t		nlen;

	nlen = ft_strlen(needle);
	while (*havstack)
	{
		ii = 0;
		while (havstack[ii] && ii < nlen)
			if (havstack[ii] == needle[ii])
				ii++;
			else
				break;
		if (ii == nlen)
			return (char *)havstack;
		havstack++;
	}
	return NULL;
}
