#include "libft.h"

char	*ft_strupper(char **str)
{
	char	*strp;

	strp = *str;
	while (*strp)
	{
		*strp = (char)ft_toupper(*strp);
		++strp;
	}
	return (*str);
}
