#include "../libft.h"

char	*ft_setSpace(int n, size_t *nl)
{
	char	*rt;

	if (n <= 0)
		*nl += 1;
	while (n != 0)
	{
		n = n/10;
		*nl += 1;
	}
	rt = (char *)malloc(sizeof(char)*(*nl+1));
	if (rt == NULL)
		return NULL;
	return rt;
}

char	*ft_itoa(int n)
{
	char	*rt;
	int	sf;
	size_t	nl;

	nl = 0;
	sf = 1;
	rt = ft_setSpace(n, &nl);
	if (rt == NULL)
		return NULL;
	if (n < 0)
		sf = -1;
	rt[nl] = 0;
	rt[--nl] = '0' + sf * (n%10);
	n = sf * (n / 10);
	while (n != 0)
	{
		rt[--nl] = '0' + n%10;
		n = n / 10;
	}
	if (nl)
		rt[0] = '-';
	return rt;
}
