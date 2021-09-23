#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;

	data = malloc(count * size);
	if (!data)
		return (NULL);
	return (ft_memset(data, 0, count * size));
}
