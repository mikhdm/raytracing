#include "canvas.h"
#include "parsing/errors.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/*
* data which are more than 1 byte size is stored in little-endian.
 */
static void	set_bitmapfileheader(t_data *data, unsigned char header[14])
{
	int				size;
	unsigned int	offset;

	offset = 54;
	size = (data->screen->width * data->screen->height * (data->bpp / 8)
			+ (int)offset);
	ft_memset(header, 0, 14);
	header[0] = 0x42;
	header[1] = 0x4D;
	header[2] = size;
	header[3] = size >> 8;
	header[4] = size >> 16;
	header[5] = size >> 24;
	header[10] = offset;
}

static void	set_bitmapinfoheader(t_data *data, unsigned char header[40])
{
	ft_memset(header, 0, 40);
	header[0] = 40;
	header[4] = data->screen->width;
	header[5] = data->screen->width >> 8;
	header[6] = data->screen->width >> 16;
	header[7] = data->screen->width >> 24;
	header[8] = data->screen->height;
	header[9] = data->screen->height >> 8;
	header[10] = data->screen->height >> 16;
	header[11] = data->screen->height >> 24;
	header[12] = 1;
	header[14] = data->bpp;
}

static void	put_image_line(t_data *data, int fd, ssize_t i, unsigned char *line)
{
	ssize_t			j;
	unsigned int	color;
	ssize_t			nbytes;

	j = 0;
	nbytes = data->screen->width * (data->bpp / 8);
	ft_bzero(line, nbytes);
	while (j < data->screen->width * (data->bpp / 8))
	{
		color = *(unsigned int *)(data->addr + (i * data->length + j));
		line[j] = color;
		line[j + 1] = color >> 8;
		line[j + 2] = color >> 16;
		j += 4;
	}
	write(fd, line, nbytes);
}

static void	put_image(t_data *data, int fd)
{
	ssize_t			i;
	ssize_t			nbytes;
	unsigned char	*line;

	nbytes = data->screen->width * (data->bpp / 8);
	if (!alloca_to((void **)&line, nbytes))
	{
		close(fd);
		ft_pexitfree(ERROR_ERRNO, errno, data);
	}
	i = data->screen->height - 1;
	while (i >= 0)
		put_image_line(data, fd, i--, line);
	free(line);
}

void	screenshot(t_data *data, char const *filename)
{
	int				fd;
	ssize_t			status;
	unsigned char	BITMAPFILEHEADER[14];
	unsigned char	BITMAPINFOHEADER[40];

	set_bitmapfileheader(data, BITMAPFILEHEADER);
	set_bitmapinfoheader(data, BITMAPINFOHEADER);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	status = write(fd, BITMAPFILEHEADER, 14);
	if (status == -1)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	status = write(fd, BITMAPINFOHEADER, 40);
	if (status == -1)
		ft_pexitfree(ERROR_ERRNO, errno, data);
	put_image(data, fd);
	close(fd);
}
