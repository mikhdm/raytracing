#include <stddef.h>

size_t	ft_strslen(char **strs)
{
	size_t	cnt;

	cnt = 0;
	while (*strs)
	{
		++strs;
		++cnt;
	}
	return (cnt);
}
