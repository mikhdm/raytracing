#include <stdlib.h>
#include "libft.h"

static char	ft_itoa_check_and_modif(int *n)
{
	char	flags;

	flags = 0;
	if (*n < 0)
	{
		flags |= (1 << 1);
		if (*n == INT_MIN)
		{
			flags |= (1 << 2);
			*n += 1;
		}
		*n *= -1;
	}
	return (flags);
}

static short int	ft_isneg(char flags)
{
	return ((flags & (1 << 1)) == (1 << 1));
}

static short int	ft_ismin(char flags)
{
	return ((flags & (1 << 2)) == (1 << 2));
}

static size_t	ft_itoa_strlen(int n, char flags)
{
	size_t	size;

	size = 0;
	while (n)
	{
		++size;
		n /= 10;
	}
	if (ft_isneg(flags))
		++size;
	return (size);
}

char	*ft_itoa(int n)
{
	size_t		size;
	char		*nbr;
	char		flags;

	if (!n)
		return (ft_strdup("0"));
	flags = ft_itoa_check_and_modif(&n);
	size = ft_itoa_strlen(n, flags);
	nbr = malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (NULL);
	nbr[size--] = '\0';
	if (ft_ismin(flags))
	{
		nbr[size--] = (n % 10) + 1 + '0';
		n /= 10;
	}
	while (n)
	{
		nbr[size--] = (n % 10) + '0';
		n /= 10;
	}
	if (ft_isneg(flags))
		nbr[size] = '-';
	return (nbr);
}
