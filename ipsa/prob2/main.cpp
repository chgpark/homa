#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF 1000

void		find_comp(int i, int count, char *comp, char *str)
{
	if (count > i)
	{
		*comp = 0;
		comp = str;
		count = 0;
		i = 0;
		while ((*comp >= '0') && (*comp <= '9') || *comp == ' ')
		{
			if (*comp != ' ')
				i = *comp - '0' + 10 * i;
			comp++;
		}
		count = count + i;
		while (*comp)
		{
			i = 0;
			if (*comp == '+')
			{
				comp++;
				while ((*comp >= '0') && (*comp <= '9') || *comp == ' ')
				{
					if (*comp != ' ')
						i = *comp - '0' + 10 * i;
					comp++;
				}
				count = count + i;
			}
			else if (*comp == '-')
			{
				comp++;
				while ((*comp >= '0') && (*comp <= '9') || *comp == ' ')
				{
					if (*comp != ' ')
						i = *comp - '0' + 10 * i;
					comp++;
				}
				count = count - i;
			}
		}
		if (count == 0)
			printf("%s\n", str);
		return ;
	}
	*(comp + 1) = count + '0';
	*comp = ' ';
	find_comp(i, count + 1, comp + 2, str);
	*comp = '+';
	find_comp(i, count + 1, comp + 2, str);
	*comp = '-';
	find_comp(i, count + 1, comp + 2, str);
}

int		main(int ac, char **av)
{
	char	str[BUF];
	char	*tmp;
	char	comp[18];
	int	n;
	int	count;

	comp[17] = 0;
	n = 0;
	read(1, str, BUF);
	tmp = str;
	while (*tmp != '\n')
		n = *tmp++ - '0' + n * 10;
	char	sve[n];
	count = -1;
	while (++count < n)
	{
		read(1, str, BUF);
		sve[count] = *str;
	}
	count = -1;
	comp[0] = '1';
	while (++count < n)
	{
		find_comp(sve[count] - '0', 2, comp+1, comp);
		if (count != n-1)
			printf("\n");
	}
	return 0;
}
