#include "../libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**rt;
	size_t	ii, jj, sgn;

	ii = -1;
	sgn = 1;
	while (s[++ii])
		if (s[ii] == c)
		{
			sgn++;
			while (s[ii] == c && s[ii])
				ii++;
		}
	rt = (char **) malloc(sizeof(char *) * (sgn+1));
	rt[sgn] = 0;
	if (rt == NULL)
		return NULL;
	ii = 0;
	sgn = 0;
	while (s[ii])
		if (s[ii] != c)
		{
			jj = ii;
			while (s[jj] != c && s[jj])
				jj++;
			rt[sgn] = ft_strsub(s, ii, jj-ii);
			sgn++;
			ii = jj;
		}
		else
			ii++;
	return rt;
}
