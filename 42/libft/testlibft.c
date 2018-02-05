#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	tnum;
static int	testn;

int		main(int ac, char **av)
{
	int		ii;
	int		prev;
	int		options;
	int	testx;
	char	*org;
	char	*orgs;
	char	*tb;
	int	orgn;
	int	tbn;
	char	*tmp;
	void	*orgr;
	char	*orgc;
	void	*tbr;
	char	*tbc;

	orgs = NULL;
	tnum = 0;
	testn = 0;
	while ((options = getopt(ac, av, "n:t:")) != -1)
	{
		switch (options)
		{
			case 'n': tnum = atoi(optarg); break;
			case 't': testn = atoi(optarg); break;
			default: break;
		}
	}
	srand(time(0));
	ac = rand() % 40;
	org = (char *)malloc(sizeof(char)*ac);
	tb = (char *)malloc(sizeof(char)*ac);
	if (org == NULL || tb == NULL)
	{
		printf("malloc error\n");
		return -1;
	}
	ii = ac;
	tmp = org;
	while (ii-- > 0)
	{
		*tmp = rand() % 127;
		tmp++;
	}
	memcpy(tb, org, ac);
	prev = ac;
	ac = rand() % 40;
	// TEST # 1
	if (tnum == 1)
	{
		if (testn)
		{
			memset(org, 1, testn);
			ft_memset(tb, 1, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("org : %d\t\ttest : %d\n", (int)org[ac], (int)tb[ac]);
		}
		else
		{
			testn = rand() % 20;
			memset(org, 1, testn);
			ft_memset(tb, 1, testn);
			ii = ac;
			while (ii-- > 0)
				if (org[ii] != tb[ii])
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("org : %d\t\ttest : %d\n", (int)org[ii], (int)tb[ii]);
				}
		}
	}
	// TEST # 2
	else if (tnum == 2)
	{
		if (testn)
		{
			bzero(org, testn);
			ft_bzero(tb, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("org : %d\t\ttest : %d\n", (int)org[ac], (int)tb[ac]);
		}
		else
		{
			testn = rand() % 20;
			bzero(org, testn);
			ft_bzero(tb, testn);
			ii = ac;
			while (ii-- > 0)
				if (org[ii] != tb[ii])
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("org : %d\t\ttest : %d\n", (int)org[ii], (int)tb[ii]);
				}
		}
	}
	// TEST # 3
	else if (tnum == 3)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 127;
			tmp++;
		}
		if (testn)
		{
			memcpy(org, orgs, testn);
			ft_memcpy(tb, orgs, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("org : %d\t\ttest : %d\n", (int)org[ac], (int)tb[ac]);
		}
		else
		{
			testn = rand() % 20;
			memcpy(org, orgs, testn);
			ft_memcpy(tb, orgs, testn);
			ii = ac;
			while (ii-- > 0)
				if (org[ii] != tb[ii])
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("org : %d\t\ttest : %d\n", (int)org[ii], (int)tb[ii]);
				}
		}
	}
	// TEST # 4
	else if (tnum == 4)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 127;
			tmp++;
		}
		if (testn)
		{
			orgr = memccpy(org, orgs, 80, testn);
			tbr = ft_memccpy(tb, orgs, 80, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("# : %d\t\torg : %d\t\ttest : %d\t\torgs : %d\n", ac, (int)org[ac], (int)tb[ac], (int)orgs[ac]);
			printf("org : %p\t\ttest : %p\n", orgr, tbr);
			printf("org : %d\t\ttest : %d\n", (int)*((char *)orgr), (int)*((char *)tbr));
		}
		else
		{
			testx = rand() % 127;
			testn = rand() % 20;
			memccpy(org, orgs, testx, testn);
			ft_memccpy(tb, orgs, testx, testn);
			ii = ac;
			while (ii-- > 0)
				if (org[ii] != tb[ii])
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("org : %d\t\ttest : %d\n", (int)org[ii], (int)tb[ii]);
				}
		}
	}
	// TEST # 5
	else if (tnum == 5)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 127;
			tmp++;
		}
		if (testn)
		{
			orgr = memmove(org, orgs, testn);
			tbr = ft_memmove(tb, orgs, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("# : %d\t\torg : %d\t\ttest : %d\t\torgs : %d\n", ac, (int)org[ac], (int)tb[ac], (int)orgs[ac]);
		}
		else
		{
			testn = rand() % 20;
			memmove(org, orgs, testn);
			ft_memmove(tb, orgs, testn);
			ii = ac;
			while (ii-- > 0)
				if (org[ii] != tb[ii])
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("org : %d\t\ttest : %d\n", (int)org[ii], (int)tb[ii]);
				}
		}
	}
	// TEST # 6
	else if (tnum == 6)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 95 + 31;
			tmp++;
		}
		if (testn)
		{
			orgr = memchr(orgs, 80, testn);
			tbr = ft_memchr(orgs, 80, testn);
			while (ac-- > 0)
				printf("# : %d\t\torgs : %d\t\taddr : %p\n", ac, (int)orgs[ac], orgs+ac);
			printf("orgr : %p\t\ttestb : %p\n\n", orgr, tbr);
		}
		else
		{
			testn = rand() % 20;
			testx = rand() % 127;
			orgr = memchr(orgs, testx, testn);
			tbr = ft_memchr(orgs, testx, testn);
			ii = ac;
			if (orgr != tbr)
			{
				while (ii-- > 0)
					printf("# : %d\t\torgs : %d\t\taddr : %p\n", ac, (int)orgs[ac], orgs+ac);
				printf("orgr : %p\t\ttestb : %p\n\n", orgr, tbr);
			}
		}
	}
	// TEST # 7
	else if (tnum == 7)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 127;
			tmp++;
		}
		if (testn)
		{
			orgn = memcmp(org, orgs, testn);
			tbn = ft_memcmp(tb, orgs, testn);
			printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
			while (ac-- > 0)
				printf("# : %d\t\torg : %d\t\ttest : %d\t\torgs : %d\n", ac, (int)org[ac], (int)tb[ac], (int)orgs[ac]);
			printf("orgn : %d\t\ttbn : %d\n", orgn, tbn);
		}
		else
		{
			testn = rand() % 20;
			orgn = memcmp(org, orgs, testn);
			tbn = ft_memcmp(tb, orgs, testn);
			ii = ac;
			while (ii-- > 0)
				if (orgn != tbn)
				{
					printf("orgb : %d\t\ttestb : %d\n\n", (int)*(org+ac+2), (int)*(tb+ac+2));
					ii = ac;
					while (ii-- > 0)
						printf("# : %d\t\torg : %d\t\ttest : %d\t\torgs : %d\n", ii, (int)org[ii], (int)tb[ii], (int)orgs[ii]);
					printf("orgn : %d\t\ttbn : %d\n", orgn, tbn);
				}
		}
	}
	// TEST # 8
	else if (tnum == 8)
	{
		orgn = strlen(org);
		tbn = ft_strlen(org);
		printf("org : %d\t\ttb : %d\n", orgn, tbn);
		if (orgn != tbn)
			while (ac-->0)
				printf("# : %d\t\torgs : %d\n", ac, (int)org[ac]);
	}
	// TEST # 9
	else if (tnum == 9)
	{
		orgc = strdup(org);
		tbc = ft_strdup(org);
		printf("org : %s\ntest : %s\norgs : %s\n", orgc, tbc, org);
		free(orgc);
		free(tbc);
	}
	// TEST # 10
	else if (tnum == 10)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
		{
			*tmp = rand() % 127;
			tmp++;
		}
		strcpy(org, orgs);
		ft_strcpy(tb, orgs);
		printf("org : %s\ntest : %s\norgs : %s\n", org, tb, orgs);
	}
	// TEST # 11
	else if (tnum == 11)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
			tmp[ii] = rand() % 96 + 31;
		orgn = rand() % 40;
		strncpy(org, orgs, orgn);
		ft_strncpy(tb, orgs, orgn);
		ii = prev;
		while (ii-->0)
			if (org[ii] != tb[ii])
				printf("org : %d\t\ttest : %d\t\torgs : %d\t\tn: %d\n", (int)org[ii], (int)tb[ii], (int)orgs[ii], ii);
		printf("n : %d\t\torg : %s\t\ttest : %s\t\torgs : %s\n", orgn, org, tb, orgs);
	}
	// TEST # 12
	else if (tnum == 12)
	{
		memset(tb, 0, sizeof(prev));
		memset(org, 0, sizeof(prev));
		if (prev)
		{
			*tb = 'a';
			*org = 'a';
		}
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
			tmp[ii] = rand() % 96 + 31;
		strcat(org, orgs);
		ft_strcat(tb, orgs);
		ii = prev;
		while (ii-->0)
			if (org[ii] != tb[ii])
				printf("org : %d\t\ttest : %d\t\torgs : %d\t\tn: %d\n", (int)org[ii], (int)tb[ii], (int)orgs[ii], ii);
		printf("n : %d\t\torg : %s\t\ttest : %s\t\torgs : %s\n", prev, org, tb, orgs);
	}
	// TEST # 13
	else if (tnum == 13)
	{
		memset(tb, 0, sizeof(prev));
		memset(org, 0, sizeof(prev));
		if (prev)
		{
			*tb = 'a';
			*org = 'a';
		}
		orgn = rand() % ac;
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
			tmp[ii] = rand() % 96 + 31;
		strncat(org, orgs, orgn);
		ft_strncat(tb, orgs, orgn);
		ii = prev;
		while (ii-->0)
			if (org[ii] != tb[ii])
				printf("org : %d\t\ttest : %d\t\torgs : %d\t\tn: %d\n", (int)org[ii], (int)tb[ii], (int)orgs[ii], ii);
		printf("n : %d\t\torg : %s\t\ttest : %s\t\torgs : %s\n", orgn, org, tb, orgs);
	}
	// TEST # 14
	else if (tnum == 14)
	{
		memset(tb, 0, sizeof(prev));
		memset(org, 0, sizeof(prev));
		if (prev)
		{
			*tb = 'a';
			*org = 'a';
		}
		orgn = rand() % ac;
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		tmp = orgs;
		while (ii-- > 0)
			tmp[ii] = rand() % 96 + 31;
		tbn = ft_strlcat(tb, orgs, orgn);
		ii = prev;
		printf("n : %d\t\torgn : %d\t\ttest : %s\t\torgs : %s\n", tbn, orgn, tb, orgs);
	}
	if (orgs)
		free(orgs);
	free(org);
	free(tb);
	return 0;
}
