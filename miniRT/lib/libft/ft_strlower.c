#include "libft.h"

char	*ft_strlower(char **str)
{
	char	*strp;

	strp = *str;
	while (*strp)
	{
		*strp = (char)ft_tolower(*strp);
		++strp;
	}
	return (*str);
}
