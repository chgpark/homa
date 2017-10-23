#include <stdio.h>
#include <unistd.h>

#define BUF 10000

int		main(int ac, char **av)
{
	char	str[BUF];
	char	*chk;		// main check
	char	*tmp;		// temp 5 char check
	char	key[5][6];
	int	i;
	int	j;		//number of char
	int	sum;
	int	ret;

	i = 0;
	while (i < 5)
		key[i++][5] = 0;
	i = 0;
	ret = read(1, str, sizeof(str));
	str[ret] = '\0';
	tmp = str;
	while (*tmp)
	{
		if ((48 > *tmp || 57 < *tmp) && (65 > *tmp || 90 < *tmp)) //벗어나는것 발견 현재키 리셋
			*tmp = 37;
		else if (47 < *tmp && 58 > *tmp)
			*tmp = *tmp - 47;
		else
			*tmp = *tmp - 54;
		tmp++;
	}
	chk = str;
	while (*chk)
	{
//		if ((48 > *tmp || 57 < *tmp) && (65 > *tmp || 90 < *tmp))
		tmp = chk;
		j = 0;
		while (*tmp)
		{
			if ((48 > *tmp || 57 < *tmp) && (65 > *tmp || 90 < *tmp)) //벗어나는것 발견 현재키 리셋
			{
				chk++;
				break;
			}
			key[i][j] = *tmp;
			if (i == 0 && j == 4)
			{
				sum = (key[i][0] * 3 + key[i][1] * 5 + key[i][2] * 7 + key[i][3] * 11) % 36;
			printf("%d", sum);
				if (sum == (key[i][4] - 55))
				{
					i++;
					chk += 5;
					break;
					printf("23");
				}
				else
				{
					chk++;
					break;
				}
			}
			else if (j == 4)
			{
				sum = (key[i-1][4] * 2 + key[i][0] * 3 + key[i][1] * 5 + key[i][2] * 7 + key[i][3] * 11) % 36;
				if (sum == (key[i][4] - 55))
				{
					i++;
					chk += 5;
					break;
				}
				else
				{
					chk++;
					break;
				}
			}
			j++;
			tmp++;
		}
		if (i == 4)
			break;
	}
	printf("%s\n", key[0]);
	return 0;
}
