#include "canvas.h"
#include "libft.h"
#include "utils.h"
#include "parsing/errors.h"
#include "parsing/serialize.h"
#include <errno.h>

t_data	*serialize(t_data *data, char *line, char **initial)
{
	const char				*label[] = {LABEL_RESOLUTION, LABEL_AMBIENCE,
					   LABEL_CAMERA, LABEL_LIGHT, LABEL_SPHERE, LABEL_CYLINDER,
					   LABEL_PLANE, LABEL_TRIANGLE, LABEL_SQUARE, NULL};
	const t_serialize_func	func[] = {&serialize_r, &serialize_a, &serialize_c,
							&serialize_l, &serialize_sp, &serialize_cy,
							&serialize_pl, &serialize_tr, &serialize_sq};
	char					**strs;
	size_t					i;

	strs = ft_splitf(line, &ft_isspace);
	free(*initial);
	if (!strs)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	if (!one_of(strs[0], label))
		serialize_error(ERROR_SYNTAX, 255, data, strs);
	i = 0;
	while (i < NUM_LABELS)
	{
		if (ft_strcmp(strs[0], label[i]) == 0)
			data = (func[i])(data, strs);
		++i;
	}
	ft_strsfree(strs);
	return (data);
}

void	serialize_error(int code, int status, t_data *data, char **strs)
{
	if (strs)
		ft_strsfree(strs);
	if (data)
		ft_pexitfree(code, status, data);
	ft_pexit(code, status);
}
