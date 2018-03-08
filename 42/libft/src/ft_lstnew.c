#include "../libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*rt;

	rt = (t_list *)malloc(sizeof(t_list));
	if (rt == NULL)
		return NULL;
	rt->next = NULL;
	rt->content_size = content_size;
	rt->content = (void *)malloc(content_size);
	if (content == NULL || rt->content == NULL)
	{
		rt->content = NULL;
		rt->content_size = 0;
		return rt;
	}
	ft_memcpy(rt->content, content, content_size);
	return rt;
}
