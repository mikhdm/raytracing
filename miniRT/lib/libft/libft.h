#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <sys/types.h>

# define FALSE 0
# define TRUE 1

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# define IN 0
# define OUT 1

# define STDOUT 0
# define STDIN 1
# define STDERR 2

# define ST_EMPTY 0
# define ST_DOT 1
# define ST_DOTLEFT 2
# define ST_DOTRIGHT 4
# define ST_EXPSIGN 8
# define ST_EXPVAL 16

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_until(const char *s, const char sym);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack,
						const char *needle,
						size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
double				ft_atof(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strdup_until(const char *s1, const char sym);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_split_any(char const *s, char c);
char				**ft_splitf(char const *s, int (*f)(int));
size_t				ft_strslen(char **strs);
void				ft_strsfree(char **strs);
char				*ft_strlower(char **str);
char				*ft_strupper(char **str);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
ssize_t				ft_max(ssize_t left, ssize_t right);
ssize_t				ft_min(ssize_t left, ssize_t right);
short				ft_isfloatable(const char *str);
short				ft_fequal(double left, double right);
short				ft_flt(double left, double right);
short				ft_fgt(double left, double right);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst,
						void *(*f)(void *),
						void (*del)(void *));

#endif
