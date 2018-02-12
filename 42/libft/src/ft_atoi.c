#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	ii;
	size_t	nlen;
	int	ret;

	nlen = ft_strlen(nptr);
	ii = 0;
	ret = 0;
	if (nptr[ii] == '+' || nptr[ii] == '-')
		ii++;
	while (nptr[ii] >= '0' && nptr[ii] <= '9' && nlen-- > 0)
	{
		ret = ret*10 + nptr[ii] - '0';
		ii++;
	}
	if (nptr[0] == '-')
		return -ret;
	else
		return ret;
}	
