#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;

	curr = NULL;
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (NULL);
	curr = head;
	lst = lst->next;
	while (lst)
	{
		curr->next = ft_lstnew(f(lst->content));
		if (!curr->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		curr = curr->next;
		lst = lst->next;
	}
	return (head);
}
