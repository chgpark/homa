#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *))
{
	if (lst == NULL)
		return;
	f(lst);
	ft_lstiter(lst->next, f);
}
