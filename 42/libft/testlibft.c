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
	int		jj;
	int		prev;
	int		options;
	char	tstr[1000];
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
	char	*orgm;

	orgs = NULL;
	tnum = 0;
	testn = 0;
	ft_memset(tstr, 0, sizeof(tstr));
	while ((options = getopt(ac, av, "n:t:i:")) != -1)
	{
		switch (options)
		{
			case 'n': tnum = atoi(optarg); break;
			case 't': testn = atoi(optarg); break;
			case 'i': jj = ft_strlen(optarg); ft_memcpy(tstr, optarg, jj); break;
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
	// TEST # 15
	else if (tnum == 15)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		orgn = (int)orgs[rand() % ac];
		orgc = strchr(orgs, orgn);
		tbc = ft_strchr(orgs, orgn);
		if (orgc != tbc)
			printf("org: %p\t\ttb: %p\n", orgc, tbc);
		printf("orgs: %s\t\torgn: %d\n", orgs, orgn);
		printf("org: %p\t\ttb: %p\n", orgc, tbc);
	}
	// TEST # 16
	else if (tnum == 16)
	{
		orgs = (char *)malloc(sizeof(char)*ac);
		if (orgs == NULL)
			return -1;
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		orgn = (int)orgs[rand() % ac];
		orgc = strrchr(orgs, orgn);
		tbc = ft_strrchr(orgs, orgn);
		if (orgc != tbc)
			printf("org: %p\t\ttb: %p\n", orgc, tbc);
		printf("orgs: %s\t\torgn: %d\n", orgs, orgn);
		printf("org: %p\t\ttb: %p\n", orgc, tbc);
	}
	// TEST # 17
	else if (tnum == 17)
	{
		orgs = (char *)malloc(sizeof(char)*(ac+10));
		orgm = (char *)malloc(sizeof(char)*(ac+1));
		memset(orgm, 0, ac);
		if (orgs == NULL)
			return -1;
		ii = ac+10;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		ii = 0;
		while (ii < ac)
		{
			orgm[ii] = orgs[ii+5];
			ii++;
		}
		orgm[ii] = 0;
		orgc = strstr(orgs, orgm);
		tbc = ft_strstr(orgs, orgm);
		if (orgc != tbc)
			printf("org: %p\t\ttb: %p\n", orgc, tbc);
		printf("orgs: %s\t\torgn: %s\n", orgs, orgm);
		printf("org: %p\t\ttb: %p\n", orgc, tbc);
	}
	// TEST # 18
	else if (tnum == 18)
	{
		orgs = (char *)malloc(sizeof(char)*(ac + 11));
		orgm = (char *)malloc(sizeof(char)*(ac + 1));
		memset(orgm, 0, ac);
		if (orgs == NULL)
			return -1;
		ii = ac + 9;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		orgs[ac+10] = 0;
		ii = 0;
		while (ii < ac)
		{
			orgm[ii] = orgs[ii+5];
			ii++;
		}
		orgm[ii] = 0;
		tbc = ft_strnstr(orgs, orgm, testn);
		printf("orgs: %s\t\torgm: %s\n", orgs, orgm);
		printf("org: %p\t\ttb: %p\n", orgs+5, tbc);
	}
	// TEST # 19
	else if (tnum == 19)
	{
		orgs = (char *)malloc(sizeof(char)*(ac + 1));
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand() % 96 + 31;
		orgs[ac] = 0;
		orgn = strcmp(org, orgs);
		tbn = ft_strcmp(org, orgs);
		if (orgn != tbn)
			printf("orgn: %d\t\ttbn: %d\n", orgn, tbn);
		printf("orgn: %d\t\ttbn: %d\n", orgn, tbn);
	}
	// TEST # 20
	else if (tnum == 20)
	{
		orgs = (char *)malloc(sizeof(char)*(ac + 1));
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand() % 96 + 31;
		orgs[ac] = 0;
		orgs = "Hello";
		orgm = "Helloaa";
		orgn = strncmp(orgm, orgs, testn);
		tbn = ft_strncmp(orgm, orgs, testn);
		if (orgn != tbn)
			printf("orgn: %d\t\ttbn: %d\n", orgn, tbn);
		printf("orgn: %d\t\ttbn: %d\n", orgn, tbn);
		printf("orgn: %s\t\ttbn: %s\n", orgm, orgs);
	}
	// TEST # 21
	else if (tnum == 21)
	{
		orgn = atoi(tstr);
		tbn = ft_atoi(tstr);
		printf("orgn: %d\t\ttbn: %d\t\tstring: %s\n", orgn, tbn, tstr);
	}
	// TEST # 22
	else if (tnum == 22)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 96 + 31;
		orgn = isalpha(orgs[0]);
		tbn = ft_isalpha(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
	}
	// TEST # 23
	else if (tnum == 23)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 96 + 31;
		orgn = isdigit(orgs[0]);
		tbn = ft_isdigit(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
	}
	// TEST # 24
	else if (tnum == 24)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 96 + 31;
		orgn = isalnum(orgs[0]);
		tbn = ft_isalnum(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %c\n", orgn, tbn, orgs[0]);
	}
	if (orgs)
		free(orgs);
	free(org);
	free(tb);
	return 0;
}
