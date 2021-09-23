#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*data;
	unsigned int	size;
	unsigned int	i;

	if (!f)
		return (NULL);
	size = ft_strlen(s);
	data = malloc(sizeof(char) * (size + 1));
	if (!data)
		return (NULL);
	i = 0;
	while (i < size)
	{
		data[i] = f(i, s[i]);
		++i;
	}
	data[i] = '\0';
	return (data);
}
