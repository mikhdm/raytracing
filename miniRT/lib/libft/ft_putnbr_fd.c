#include <unistd.h>
#include "libft.h"

static void	ft_putpnbr_fd(unsigned int n, int fd, char neg)
{
	char	d;

	if (n == 0)
		return ;
	if (n)
		ft_putpnbr_fd(n / 10, fd, neg);
	if (neg && (n == INT_MAX))
		d = (n % 10) + 1 + '0';
	else
		d = n % 10 + '0';
	write(fd, &d, sizeof(char));
}

void	ft_putnbr_check_and_modif(int *n, char *neg, char *min)
{
	if (*n < 0)
	{
		*neg = TRUE;
		if (*n == INT_MIN)
		{
			*min = TRUE;
			*n += 1;
		}
		(*n) *= -1;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	d;
	char	neg;
	char	min;

	neg = FALSE;
	min = FALSE;
	if (fd < 0)
		return ;
	ft_putnbr_check_and_modif(&n, &neg, &min);
	if (n == 0)
	{
		d = '0';
		write(fd, &d, sizeof(char));
		return ;
	}
	if (neg)
	{
		d = '-';
		write(fd, &d, sizeof(char));
	}
	ft_putpnbr_fd(n, fd, neg);
}
