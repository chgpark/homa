#include "../libft.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n < -9)
			ft_putnbr(-(n/10));
		ft_putnbr(-(n%10));
	}
	else if (n < 10)
		ft_putchar('0'+n);
	else
	{
		ft_putnbr(n/10);
		ft_putchar('0'+n%10);
	}
	
}
