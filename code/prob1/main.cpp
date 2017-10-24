#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF 10000

typedef struct		s_key
{
	struct s_key	*next;
	char		key[5][6];
}			t_key;

t_key		*ft_create_elem(char data[5][6])
{
	int		i;
	int		j;
	t_key		*rt;

	rt = (t_key*) malloc(sizeof(t_key));
	if (rt)
	{
		rt->next = NULL;
		i = 0;
		while (i < 5)
		{
			j = 0;
			while (j < 5)
			{
				rt->key[i][j] = data[i][j];
				j++;
			}
			rt->key[i][j] = 0;
			i++;
		}
	}
	return (rt);
}

void	ft_list_push_back(t_key **begin_list, char data[5][6])
{
	t_key		*list;
	t_key		*rt;

	rt = ft_create_elem(data);
	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = rt;
	}
	else
		*begin_list = rt;
}

int		main(int ac, char **av)
{
	//	initialize
	char	str[BUF];
	char	*chk;		// main check
	char	*tmp;		// temp 5 char check
	char	key[5][6];
	t_key	*key_list;
	int	i;
	int	j;		//number of char
	int	sum;
	int	ret;

	i = 0;
	while (i < 5)
		key[i++][5] = 0;

	//	read the input
	i = 0;
	ret = read(1, str, sizeof(str));
	str[ret] = '\0';

	//	change to simple number
	tmp = str;
	while (*tmp)
	{
		if ((48 > *tmp || 57 < *tmp) && (65 > *tmp || 90 < *tmp))
			*tmp = 37;
		else if (47 < *tmp && 58 > *tmp)
			*tmp = *tmp - 47;
		else
			*tmp = *tmp - 54;
		tmp++;
	}

	//	find out
	chk = str;
	while (*chk)
	{
		tmp = chk;
		j = 0;
		while (*tmp && (*tmp != 37))
		{
			key[i][j] = *tmp;
			if (i == 0 && j == 4)
			{
				sum = ((key[i][0] - 1) * 3 + (key[i][1] - 1) * 5 + (key[i][2] - 1) * 7 + (key[i][3] - 1) * 11) % 36;
				if (sum == (key[i][4] - 1))
				{
					i++;
					chk += 5;
					break;
				}
				else
				{
					key[i][0] = 0;
					key[i][1] = 0;
					key[i][2] = 0;
					key[i][3] = 0;
					key[i][4] = 0;
					chk++;
					break;
				}
			}
			else if (j == 4)
			{
				sum = ((key[i-1][4] - 1) * 2 + (key[i][0] - 1) * 3 + (key[i][1] - 1) * 5 + (key[i][2] - 1) * 7 + (key[i][3] - 1) * 11) % 36;
				if (sum == (key[i][4] - 1))
				{
					chk += 5;
					if (i == 4)
					{
						//change to original key
						i = 0;
						while (i < 5)
						{
							j = 0;
							while (j < 5)
							{
								if ((0 < key[i][j]) && (11 > key[i][j]))
									key[i][j] = key[i][j] + 47;
								else if ((10 < key[i][j]) && (37 > key[i][j]))
									key[i][j] = key[i][j] + 54;
								j++;
							}
							i++;
						}
						//save in the list
						ft_list_push_back(&key_list, key);
						i = 0;
						while (i < 5)
						{
							key[i][0] = 0;
							key[i][1] = 0;
							key[i][2] = 0;
							key[i][3] = 0;
							key[i][4] = 0;
							i++;
						}
						i = -1;
					}
					i++;
					break;
				}
				else
				{
					key[i][0] = 0;
					key[i][1] = 0;
					key[i][2] = 0;
					key[i][3] = 0;
					key[i][4] = 0;
					chk++;
					break;
				}
			}
			j++;
			tmp++;
			if (!(*tmp) || *tmp == 37)
			{	
				key[i][0] = 0;
				key[i][1] = 0;
				key[i][2] = 0;
				key[i][3] = 0;
				key[i][4] = 0;
			}
		}
		if (!(*tmp) || (*tmp == 37))
			chk++;
	}

	//print out
	while (key_list)
	{
		printf("%s-%s-%s-%s-%s", key_list->key[0], key_list->key[1], key_list->key[2], key_list->key[3], key_list->key[4]);
		printf("\n");
		key_list = key_list->next;
	}
	return 0;
}
