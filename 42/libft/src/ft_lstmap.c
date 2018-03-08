#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*rt;
	t_list	*tmp;

	rt = f(lst);
	if (rt == NULL)
		return NULL;
	tmp = rt;
	while (lst->next)
	{
		tmp->next = f(lst->next);
		if (tmp->next == NULL)
			return NULL;
		lst = lst->next;
		tmp = tmp->next;
		
	}
	return rt;
}
