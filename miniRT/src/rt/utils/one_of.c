#include "libft.h"

short	one_of(char *value, char const **strs)
{
	while (*strs)
	{
		if (ft_strcmp(value, *strs++) == 0)
			return (TRUE);
	}
	return (FALSE);
}
