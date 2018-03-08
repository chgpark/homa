#include "../libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	slen;

	slen = ft_strlen(s);
	write(fd, s, slen);
}
