#include "libft.h"
#include <math.h>

static double	ft_powf(double v, long p)
{
	double	r;

	r = 1;
	if (p < 0)
	{
		while (p++)
			r /= v;
	}
	else
		while (p--)
			r *= v;
	return (r);
}

static double	ft_atof_infnan(char *str)
{
	double	value;

	value = 0.0;
	if (ft_strncmp(str, "-inf", 4) == 0)
		value = -INFINITY;
	else if (ft_strncmp(str, "inf", 3) == 0)
		value = INFINITY;
	else if (ft_strncmp(str, "nan", 3) == 0
		|| (ft_strncmp(str, "-nan", 4) == 0))
		value = NAN;
	return (value);
}

static double	ft_atof_basic(char **string, short neg, long i)
{
	double	value;
	char	*str;

	str = *string;
	value = ft_atoi(str);
	if (neg || (*str == '+'))
		++str;
	while (*str && *str != '.' && *str != 'e' && ft_isdigit(*str))
		++str;
	if (*str == '.')
	{
		++str;
		while (*str && (*str != 'e') && ft_isdigit(*str))
		{
			--i;
			if (neg)
				value -= (*str - '0') * (ft_powf(10, i));
			else
				value += (*str - '0') * (ft_powf(10, i));
			++str;
		}
	}
	*string = str;
	return (value);
}

static double	ft_atof_exp(char **string, double value, short neg)
{
	int		exp;
	char	*str;

	str = *string;
	if (*str == 'e' && fabs(value) != 0)
	{
		++str;
		exp = ft_atoi(str);
		value *= ft_powf(10, exp);
	}
	else if (fabs(value) == 0)
		if (neg)
			value = -value;
	*string = str;
	return (value);
}

double	ft_atof(const char *str)
{
	double	value;
	short	neg;
	char	*strl;
	char	*strp;

	neg = FALSE;
	while (ft_isspace(*str))
		++str;
	strl = ft_strdup(str);
	if (!strl)
		return (0);
	strp = strl;
	strl = ft_strlower(&strl);
	value = ft_atof_infnan(strl);
	if (isinf(value) || isnan(value))
	{
		free(strl);
		return (value);
	}
	if (*strl == '-' && *(strl + 1) != '-')
		neg = TRUE;
	value = ft_atof_basic(&strl, neg, 0);
	value = ft_atof_exp(&strl, value, neg);
	free(strp);
	return (value);
}
