#include "libft.h"

short	ft_flt(double left, double right)
{
	if ((left < right) && !ft_fequal(left, right))
		return (TRUE);
	return (FALSE);
}
