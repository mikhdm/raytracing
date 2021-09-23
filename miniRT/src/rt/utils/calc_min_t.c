#include "utils.h"
#include <math.h>

double	calc_min_t(t_pair_double values)
{
	if (values.first > values.second)
		swap_double(&values.first, &values.second);
	if (values.first < 0)
	{
		values.first = values.second;
		if (values.first < 0)
			return (INFINITY);
	}
	return (values.first);
}
