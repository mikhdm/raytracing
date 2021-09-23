#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SIG_OK 1
# define SIG_EOF 0
# define SIG_ERROR (-1)

# define READ_EOF 0
# define READ_ERROR (-1)

typedef struct s_item
{
	int				fd;
	char			*part;
	struct s_item	*next;
}					t_item;

typedef struct s_vars
{
	ssize_t			length;
	int				fd;
	char			*buff;
	char			*part;
	char			*tmp;
	char			*endl;
	t_item			*node;
}					t_vars;

int					get_next_line(int fd, char **line);

int					ft_exit(t_item **data, t_vars *v, char **line, int signal);
t_item				*ft_setnode(t_vars *v, t_item **data, char **line);

#endif
