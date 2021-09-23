#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	ssize;

	ssize = ft_strlen(s);
	substr = NULL;
	if (start >= ssize)
		return (ft_strdup(""));
	if (len > (ssize - start))
		len = ssize - start;
	if (!len)
		return (ft_strdup(""));
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
