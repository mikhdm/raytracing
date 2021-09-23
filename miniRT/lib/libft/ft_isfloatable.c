#include "libft.h"
#include <sys/types.h>

static short	validinfn(const char **string)
{
	const char	*str;
	const char	*label;
	size_t		i;
	const char	*labels[] = {"inf", "infinity", "-inf", "-infinity",
						 	"nan", "-nan"};

	label = NULL;
	str = *string;
	i = 0;
	while (i < sizeof(labels) / sizeof(*labels))
	{
		label = labels[i++];
		if (ft_strncmp(str, label,
				 ft_max(
					(ssize_t)ft_strlen(label),
					(ssize_t)ft_strlen(str))) == 0)
			return (TRUE);
	}
	return (FALSE);
}

static short	validot(const char **string, unsigned char *status)
{
	const char	*str = *string;

	if (*str == '.')
	{
		*status |= ST_DOT;
		++str;
		if (*status == ST_DOT && !ft_isdigit(*str))
			return (FALSE);
		while (ft_isdigit(*str))
		{
			*status |= ST_DOTRIGHT;
			++str;
		}
	}
	if ((*status == ST_EMPTY) || (*status == ST_DOT))
		return (FALSE);
	*string = str;
	return (TRUE);
}

/*
*
* validexp called if and only if validot is TRUE.
*
*/
static short	validexp(const char **string, unsigned char *status)
{
	const char	*str = *string;

	if (*str && *str != 'e' && *str != 'E')
		return (FALSE);
	if (*str == 'e' || *str == 'E')
	{
		*status |= ST_EXPSIGN;
		++str;
		if (*str == '+' || *str == '-')
			++str;
		if (!ft_isdigit(*str))
			return (FALSE);
		while (ft_isdigit(*str))
		{
			*status |= ST_EXPVAL;
			++str;
		}
	}
	*string = str;
	return (TRUE);
}

/*
 * state:
 * 		0b00000001 - dot exists
 * 		0b00000010 - digits on the left of dot exists
 * 		0b00000100 - digits on the right exists
 * 		0b00001000 - exp sign exists
 * 		0b00010000 - exp value exists
 */
short	ft_isfloatable(const char *str)
{
	const char		*ptr;
	unsigned char	status;

	if (validinfn(&str))
		return (TRUE);
	status = 0;
	if (*str == '-' || *str == '+')
		++str;
	ptr = str;
	if (!ft_isdigit(*ptr) && *ptr != '.')
		return (FALSE);
	while (ft_isdigit(*ptr))
	{
		status |= ST_DOTLEFT;
		++ptr;
	}
	if (status != ST_DOTLEFT && *ptr != '.')
		return (FALSE);
	if (!validot(&ptr, &status))
		return (FALSE);
	if (!validexp(&ptr, &status))
		return (FALSE);
	return (TRUE);
}
