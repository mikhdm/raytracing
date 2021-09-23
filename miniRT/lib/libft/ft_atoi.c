#include "libft.h"

static long	ft_pow(long n, long power)
{
	long	res;

	res = 1;
	while (power--)
		res *= n;
	return (res);
}

static long	ft_negate(long value, int neg)
{
	if (neg)
		value *= (-1);
	return (value);
}

int	ft_atoi(const char *str)
{
	long		result;
	const char	*end;
	int			neg;
	int			count;
	int			i;

	while (ft_isspace(*str))
		str++;
	neg = (*str == '-');
	result = 0;
	count = 0;
	i = 0;
	if (neg || (*str == '+'))
		str++;
	end = str;
	while (*end && ft_isdigit(*end))
	{
		count++;
		end++;
	}
	end--;
	while (i < count)
		result += (*end-- - '0') * ft_pow(10, i++);
	return ((int)ft_negate(result, neg));
}
