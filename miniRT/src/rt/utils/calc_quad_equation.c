#include <math.h>
#include "libft.h"
#include "utils.h"

static t_pair_double	calc_discriminant_zero(double a, double b, double c)
{
	t_pair_double	values;

	values = (t_pair_double){.first = INFINITY, .second = INFINITY};
	if (ft_fequal(a, 0) && !ft_fequal(b, 0))
		values.first = -c / b;
	else
		values.first = -0.5 * b / a;
	values.second = values.first;
	return (values);
}

t_pair_double	calc_quad_equation(double a, double b, double c)
{
	double			discriminant;
	t_pair_double	values;
	double			q;

	values = (t_pair_double){.first = INFINITY, .second = INFINITY};
	discriminant = b * b - 4 * a * c;
	if (ft_flt(discriminant, 0))
		return (values);
	else if (ft_fequal(discriminant, 0))
		values = calc_discriminant_zero(a, b, c);
	else if (ft_fgt(discriminant, 0))
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discriminant));
		else
			q = -0.5 * (b - sqrt(discriminant));
		values.first = q / a;
		values.second = c / q;
	}
	return (values);
}
