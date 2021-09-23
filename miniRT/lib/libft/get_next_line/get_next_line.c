#include "get_next_line.h"
#include "../libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	ft_read_raw_line_main(t_vars *v, char **raw_line)
{
	size_t	i;

	i = 0;
	while (TRUE)
	{
		v->length = read(v->fd, v->buff, BUFFER_SIZE);
		if (v->length <= 0)
			break ;
		i += v->length;
		v->buff[v->length] = '\0';
		v->endl = ft_strchr(v->buff, '\n');
		if (v->endl)
			break ;
		v->tmp = *raw_line;
		v->buff = malloc((i + BUFFER_SIZE + 1) * sizeof(char));
		if (!v->buff)
			return ;
		*raw_line = v->buff;
		ft_strlcpy(v->buff, v->tmp, i + BUFFER_SIZE + 1);
		v->buff += i;
		free(v->tmp);
	}
}

static char	*ft_read_raw_line(t_vars *v)
{
	char	*raw_line;

	v->buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!v->buff)
		return (NULL);
	raw_line = v->buff;
	*raw_line = '\0';
	ft_read_raw_line_main(v, &raw_line);
	if (!v->buff)
		return (NULL);
	return (raw_line);
}

static char	*ft_get_part_line(t_vars *v, t_item **data)
{
	char	*part;

	part = NULL;
	v->node = *data;
	while (v->node && (v->node->fd != v->fd))
		v->node = v->node->next;
	if (!v->node)
		return (NULL);
	v->endl = ft_strchr(v->node->part, '\n');
	if (v->endl)
	{
		part = ft_strdup_until(v->node->part, '\n');
		if (!part)
			return (NULL);
		v->tmp = v->node->part;
		v->node->part = ft_strdup_until(v->endl + 1, '\0');
		if (!v->node->part)
			return (NULL);
		free(v->tmp);
		v->tmp = NULL;
	}
	return (part);
}

static int	ft_post_proc_line(t_vars *v, t_item **data, char **line)
{
	if (v->endl)
	{
		v->part = ft_strdup_until(v->endl + 1, '\0');
		if (!v->part)
			return (ft_exit(data, v, line, SIG_ERROR));
	}
	free(v->tmp);
	v->tmp = NULL;
	if (v->length == READ_ERROR)
		return (ft_exit(data, v, line, SIG_ERROR));
	if (!(ft_setnode(v, data, line)))
		return (ft_exit(data, v, line, SIG_ERROR));
	if (v->length == READ_EOF)
		return (ft_exit(data, v, line, SIG_EOF));
	return (SIG_OK);
}

int	get_next_line(int fd, char **line)
{
	static t_item	*data = NULL;
	t_vars			v;

	v = (t_vars){.length = 0, .fd = fd, .buff = NULL,
		.part = NULL, .endl = NULL, .tmp = NULL, .node = NULL};
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (ft_exit(&data, &v, line, SIG_ERROR));
	*line = ft_get_part_line(&v, &data);
	if (*line)
		return (SIG_OK);
	*line = ft_read_raw_line(&v);
	if (!*line)
		return (ft_exit(&data, &v, line, SIG_ERROR));
	v.tmp = *line;
	*line = ft_strdup_until(v.tmp, '\n');
	if (!*line)
		return (ft_exit(&data, &v, line, SIG_ERROR));
	return (ft_post_proc_line(&v, &data, line));
}
