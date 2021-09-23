#include "libft.h"
#include <stdlib.h>

short int	alloca_to(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (FALSE);
	return (TRUE);
}
