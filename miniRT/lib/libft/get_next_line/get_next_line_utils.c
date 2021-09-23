#include "get_next_line.h"
#include "../libft.h"
#include <stdlib.h>

int	ft_exit(t_item **data, t_vars *v, char **line, int signal)
{
	t_item	**curr;
	t_item	*tmp;

	curr = data;
	tmp = NULL;
	if (v->tmp)
		free(v->tmp);
	while ((*curr) && (*curr)->fd != v->fd)
		curr = &(*curr)->next;
	tmp = *curr;
	if (tmp)
	{
		*curr = (*curr)->next;
		free(tmp->part);
		free(tmp);
		tmp = NULL;
	}
	if (line && *line && (signal == SIG_ERROR))
	{
		free(*line);
		*line = NULL;
	}
	return (signal);
}

static void	ft_setnewnode(t_vars *v, t_item **data)
{
	v->node = *data;
	*data = malloc(sizeof(t_item));
	if (!*data)
		return ;
	(*data)->part = v->part;
	(*data)->fd = v->fd;
	(*data)->next = v->node;
	v->node = *data;
}

t_item	*ft_setnode(t_vars *v, t_item **data, char **line)
{
	v->node = *data;
	while (v->node && (v->node->fd != v->fd))
		v->node = v->node->next;
	if (!v->node)
	{
		ft_setnewnode(v, data);
		if (!*data)
			return (NULL);
		return (v->node);
	}
	v->tmp = *line;
	*line = ft_strjoin(v->node->part, *line);
	if (!*line)
		return (NULL);
	free(v->tmp);
	free(v->node->part);
	v->tmp = NULL;
	v->node->part = v->part;
	return (v->node);
}
