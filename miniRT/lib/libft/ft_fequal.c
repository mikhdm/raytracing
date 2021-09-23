#include "libft.h"
#include <float.h>
#include <math.h>

short	ft_fequal(double left, double right)
{
	if (fabs(left - right) < DBL_EPSILON)
		return (TRUE);
	return (FALSE);
}
