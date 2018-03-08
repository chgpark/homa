#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	ii;

	ii = -1;
	while (s[++ii])
		f(ii, s+ii);
}
