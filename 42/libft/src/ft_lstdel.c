#include "../libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst == NULL)
		return;
	ft_lstdelone(alst, del);
	ft_lstdel(&((*alst)->next), del);
}
