#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*prev;
	t_list	*curr;

	prev = *lst;
	curr = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;
}
