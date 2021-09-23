#include <stdlib.h>

void	ft_strsfree(char **strs)
{
	char	**s;

	s = strs;
	while (*s)
		free(*s++);
	free(strs);
	strs = NULL;
}
