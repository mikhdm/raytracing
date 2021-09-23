#include "libft.h"

char	*skip_spaces_str(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	return (str);
}
