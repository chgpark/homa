#include "../libft.h"

char	*ft_strtrim(char const *s)
{
	char	*rt;
	size_t	ii[3] = {0, 0, 0};
	int	flag[2] = {1, 1};
	size_t	jj;

	ii[2] = ft_strlen(s);
	jj = -1;
	while (++jj < ii[2])
	{
		if (s[jj] != '\n' && s[jj] != ' ' && s[jj] != '\t' && flag[0])
			flag[0] = 0;
		else if (flag[0])
			ii[0]++;
		if (s[ii[2]-jj-1] != '\n' && s[ii[2]-jj-1] != ' ' && s[ii[2]-jj-1] != '\t' && flag[1])
			flag[1] = 0;
		else if (flag[1])
			ii[1]++;
	}
	ii[2] = ii[2] - ii[0] - ii[1];
	if (ii[2] <= 0)
		return NULL;
	rt = ft_strsub(s, ii[0], ii[2]);
	return rt;
}
