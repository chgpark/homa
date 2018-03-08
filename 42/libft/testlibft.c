#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	tnum;
static int	testn;

void	ft_strchrc(char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = *c - ('a' - 'A');
}
void	ft_strchrci(unsigned int ii, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = *c - ('a' - 'A');
	printf("%u\n", ii);
}
void	ft_lstfree(void *content, size_t content_size)
{
	ft_memset(content, 0, content_size);
	free(content);
}

void	ft_putnchar(void *content, size_t content_size)
{
	size_t	ii;
	char	*tmp;

	tmp = (char *)content;
	ii = 0;
	while (ii < content_size)
	{
		ft_putchar(tmp[ii]);
		ii++;
	}
}

t_list	*ft_lstrev(t_list *lst)
{
	t_list	*rt;
	char	*tmp;
	char	*buf;
	size_t	ii = 0;

	if (lst == NULL)
		return NULL;
	buf = (char *)malloc(sizeof(char)*lst->content_size);
	tmp = lst->content;
	while (ii < lst->content_size/2)
	{
		buf[ii] = tmp[lst->content_size - ii - 1];
		buf[lst->content_size - ii - 1] = tmp[ii];
		ii++;
	}
	rt = ft_lstnew(buf, lst->content_size);
	return rt;
}

int		main(int ac, char **av)
{
	int		ii;
	int		jj;
	int		prev;
	int		options;
	int	fd;
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
	char	**stra;

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
	// TEST # 25
	else if (tnum == 25)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 128;
		orgn = isascii(orgs[0]);
		tbn = ft_isascii(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, (int)orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, orgs[0]);
	}
	// TEST # 26
	else if (tnum == 26)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 128;
		orgn = isprint(orgs[0]);
		tbn = ft_isprint(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, (int)orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, orgs[0]);
	}
	// TEST # 27
	else if (tnum == 27)
	{
		orgs = (char *)malloc(sizeof(char));
		orgs[0] = rand() % 128;
		orgn = toupper(orgs[0]);
		tbn = ft_toupper(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, (int)orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, orgs[0]);
		orgn = tolower(orgs[0]);
		tbn = ft_tolower(orgs[0]);
		if (orgn != tbn)
			printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, (int)orgs[0]);
		printf("org: %d\t\ttb: %d\t\tc: %d\n", orgn, tbn, orgs[0]);
	}
	// TEST # 28
	else if (tnum == 28)
	{
		orgs = (char *)ft_memalloc(testn);
		printf("address: %p\t\tsize: %d\n",orgs, (int)*(orgs-4));
		ft_memdel((void**) &orgs);
		printf("address: %p\n",orgs);
	}
	// TEST # 29
	else if (tnum == 29)
	{
		tbc = ft_strnew(testn);
		while (testn-- > 0)
			printf("n: %d\t\tc: %d\n", testn, (int)tbc[testn]);
		ft_strdel(&tbc);
		printf("address: %p\n",tbc);
	}
	// TEST # 30
	else if (tnum == 30)
	{
		orgs = (char *)malloc(sizeof(char) * (ac+1));
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand() % 96 + 31;
		orgs[ac] = 0;
		ii = ac;
		ft_strclr(orgs);
		while (ii-- > 0)
			printf("n: %d\t\torgs: %d\n", ii, (int)orgs[ii]);
	}
	// TEST # 31
	else if (tnum == 31)
	{
		orgs = (char *)malloc(sizeof(char) * (ac+1));
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand() % 96 + 31;
		orgs[ac] = 0;
		printf("org: %s\n", orgs);
		ii = ac;
		ft_striter(orgs, &ft_strchrc);
		printf("tb: %s\n", orgs);
	}
	// TEST # 32
	else if (tnum == 32)
	{
		orgs = (char *)malloc(sizeof(char) * (ac+1));
		ii = ac;
		while (ii-- > 0)
			orgs[ii] = rand() % 96 + 31;
		orgs[ac] = 0;
		printf("org: %s\n", orgs);
		ii = ac;
		ft_striteri(orgs, &ft_strchrci);
		printf("tb: %s\n", orgs);
	}
	// TEST # 33
	else if (tnum == 33)
	{
		while (1)
		{
		scanf("%s", org);
		scanf("%s", tb);
		printf("result: %d\n", ft_strequ(org, tb));
		}
	}
	// TEST # 34
	else if (tnum == 34)
	{
		while (1)
		{
			scanf("%s", org);
			scanf("%s", tb);
			printf("result: %d\n", ft_strnequ(org,tb,testn));
		}
	}
	// TEST # 35
	else if (tnum == 35)
	{
		printf("org: %s\n", org);
		size_t	testsize;
		scanf("%lu", &testsize);
		orgs = ft_strsub(org, testn, testsize);
		printf("tb: %s\n", orgs);
	}
	// TEST # 36
	else if (tnum == 36)
	{
		tmp = "    h df\n ";
		tb = ft_strtrim(tmp);
		printf("tb: %s\n", tb);
	}
	// TEST # 37
	else if (tnum == 37)
	{
		tmp = "H&dsf&sdsd&&&&sdf&&&sd&d";
		stra = ft_strsplit(tmp, 0);
		tnum = -1;
		while (stra[++tnum] != 0)
			printf("n: %d\t\ttb: %s\t\tad: %p\n", tnum, stra[tnum], stra[tnum]);
	}
	// TEST # 38
	else if (tnum == 38)
	{
		tb = ft_itoa(-0);
		printf("tb: %s\n", tb);
		free(tb);
		tb = ft_itoa(-2147483648);
		printf("tb: %s\n", tb);
		free(tb);
		tb = ft_itoa(2147483647);
		printf("tb: %s\n", tb);
	}
	// TEST # 39
	else if (tnum == 39)
	{
		printf("%c\n", org[0]);
		ft_putchar(org[0]);
	}
	// TEST # 40
	else if (tnum == 40)
	{
		orgs = (char *)malloc(sizeof(char)*(ac+1));
		if (orgs == NULL)
			return -1;
		ii = ac;
		orgs[ac] = 0;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		ft_putstr(orgs);
	}
	// TEST # 41
	else if (tnum == 41)
	{
		orgs = (char *)malloc(sizeof(char)*(ac+1));
		if (orgs == NULL)
			return -1;
		ii = ac;
		orgs[ac] = 0;
		while (ii-- > 0)
			orgs[ii] = rand()%96 + 31;
		printf("%s\n", orgs);
		ft_putendl(orgs);
	}
	// TEST # 42
	else if (tnum == 42)
		ft_putnbr(testn);
	// TEST # 43
	else if (tnum == 43)
	{
		fd = open("test.c", O_WRONLY|O_CREAT);
		ft_putchar_fd('0', fd);
	}	
	// TEST # 44
	else if (tnum == 44)
	{
		fd = open("test.c", O_WRONLY|O_CREAT);
		ft_putstr_fd("12345", fd);
	}
	// TEST # 45
	else if (tnum == 45)
	{
		fd = open("test.c", O_WRONLY|O_CREAT);
		ft_putendl_fd("12345", fd);
	}
	// TEST # 46
	else if (tnum == 46)
	{
		fd = open("test.c", O_WRONLY|O_CREAT);
		ft_putnbr_fd(testn, fd);
	}
	// TEST # 47
	else if (tnum == 47)
	{
		t_list		*test;
		unsigned int	cc;

		test = ft_lstnew(org, 5);
		printf("content_size: %lu\t\tcontent: ", test->content_size);
		cc = 0;
		tb = (char *)test->content;
		while (cc < test->content_size)
		{
			printf("%d/", (int)tb[cc]);
			printf("%d ", (int)org[cc]);
			cc += 1;
		}
		printf("\n");
		free(test);
		test = ft_lstnew(NULL, 6);
		printf("content: NULL\t\tcontent_size: %lu\n", test->content_size);
	}
	// TEST # 48
	else if (tnum == 48)
	{
		t_list		*test;

		test = ft_lstnew(org, ac);
		tb = (char *)test->content;
		printf("org: %s\n", tb);
		ft_lstdelone(&test, ft_lstfree);
		tb = (char *)test->content;
		printf("tb: %p\n", test->content);
		printf("org: %s\n", tb);
		tb = malloc(1);
	}
	// TEST # 49
	else if (tnum == 49)
	{
		t_list		*test;
		t_list		*tmp;

		test = ft_lstnew(org, ac);
		tmp = ft_lstnew(org, ac);
		test->next = tmp;
		tb = (char *)test->content;
		printf("org: %s\n", tb);
		ft_lstdel(&test, ft_lstfree);
		tb = (char *)tmp->content;
		printf("tb: %p\n", tmp->content);
		printf("tb: %p\n", test);
		printf("org: %s\n", tb);
		tb = malloc(1);
	}
	// TEST # 50
	else if (tnum == 50)
	{
		t_list		*test;
		t_list		*tmp;

		test = ft_lstnew(org, ac);
		tmp = ft_lstnew(org, ac);
		test->next = tmp;
		
		tmp = ft_lstmap(test, ft_lstrev);
		while (test)
		{
			ft_putnchar(test->content, test->content_size);
			ft_putchar('\n');
			ft_putnchar(tmp->content, tmp->content_size);
			ft_putchar('\n');
			test = test->next;
			tmp = tmp->next;
		}
	}
	if (orgs)
		free(orgs);
	free(org);
	free(tb);
	return 0;
}
