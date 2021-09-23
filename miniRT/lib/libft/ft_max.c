#include <sys/types.h>

ssize_t	ft_max(ssize_t left, ssize_t right)
{
	if (left > right)
		return (left);
	return (right);
}
