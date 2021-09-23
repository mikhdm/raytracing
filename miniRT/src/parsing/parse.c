#include "canvas.h"
#include "utils.h"
#include "parsing/errors.h"
#include "parsing/parse.h"
#include "parsing/serialize.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

static t_data	*refine(t_data *data)
{
	t_camera	*cam;

	if (!data->screen)
		ft_pexitfree(ERROR_EMPTY_RESOLUTION, 255, data);
	if (!data->ambience)
		ft_pexitfree(ERROR_EMPTY_AMBIENCE, 255, data);
	if (!data->cam)
		ft_pexitfree(ERROR_EMPTY_CAMERA, 255, data);
	cam = data->cam;
	while (cam)
	{
		if (!(alloca_to((void **)&cam->viewport, sizeof(t_viewport))))
			ft_pexitfree(ERROR_ERRNO, errno, data);
		*(cam->viewport) = calc_viewport(data, cam);
		cam = cam->next;
	}
	return (data);
}

static t_data	*initialize(t_data *data)
{
	*data = (t_data){.bpp = 0, .length = 0, .endian = 0,
		.addr = NULL, .mlx = NULL, .window = NULL,
		.img = NULL, .fildes = -1, .screen = NULL,
		.cam = NULL, .light = NULL, .ambience = NULL,
		.figures = NULL};
	return (data);
}

/*
* populate - function which build actual data.
* line freed at serialize
*
*/
static t_data	*populate(t_data *data)
{
	char	*line;
	char	*start;
	int		state;

	line = NULL;
	while (TRUE)
	{
		state = get_next_line(data->fildes, &line);
		start = skip_spaces_str(line);
		if (*start && *start != '#')
			data = serialize(data, start, &line);
		else
			free(line);
		line = NULL;
		start = NULL;
		if ((state == SIG_EOF) || (state == SIG_ERROR))
			break ;
	}
	return (data);
}

static t_data	*build(int const fildes)
{
	t_data	*data;

	data = NULL;
	if (!alloca_to((void **)&data, sizeof(t_data)))
	{
		close(fildes);
		ft_pexit(ERROR_ERRNO, errno);
	}
	data = initialize(data);
	data->fildes = fildes;
	data = populate(data);
	data = refine(data);
	return (data);
}

t_data	*parse(char const *path)
{
	int		fd;
	t_data	*data;

	data = NULL;
	if (!path)
		ft_perror(ERROR_PATH_EMPTY);
	fd = open(path, O_RDONLY);
	if (isdir(fd) || (fd == -1))
	{
		ft_perror(ERROR_ERRNO);
		exit(errno);
	}
	data = build(fd);
	close(fd);
	data->fildes = -1;
	return (data);
}
