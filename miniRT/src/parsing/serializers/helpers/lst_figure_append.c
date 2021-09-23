#include "canvas.h"

void	lst_figure_append(t_figure **head, t_figure *new)
{
	t_figure	**curr;

	curr = head;
	if (!*curr)
		*curr = new;
	else
	{
		while ((*curr)->next)
			curr = &((*curr)->next);
		(*curr)->next = new;
	}
}
