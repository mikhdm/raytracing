#include "color.h"
#include "libft.h"
#include <stddef.h>

/*
* valid_rgb - sets into argb correct color parsed from strs_rgb if valid.
*/
short	valid_rgb(const char **strs_rgb, size_t strslen, int *argb)
{
	const char	*str = NULL;
	size_t		i;
	int			r;
	int			g;
	int			b;

	i = 0;
	while (i < strslen)
	{
		str = strs_rgb[i++];
		if (!str || !*str)
			return (FALSE);
		while (*str)
			if (!ft_isdigit(*str++))
				return (FALSE);
	}
	r = ft_atoi(strs_rgb[0]);
	g = ft_atoi(strs_rgb[1]);
	b = ft_atoi(strs_rgb[2]);
	if ((r < 0 || r > 255)
		|| (g < 0 || g > 255)
		|| (b < 0 || b > 255))
		return (FALSE);
	*argb = argb_color(0, r, g, b);
	return (TRUE);
}
