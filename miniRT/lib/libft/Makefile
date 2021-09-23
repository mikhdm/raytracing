CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -MMD

NAME = libft.a

INCLUDES = libft.h get_next_line.h

SRCS = ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memccpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strlen.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strnstr.c \
	   ft_strcmp.c \
	   ft_strncmp.c \
	   ft_atoi.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_isspace.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_split_any.c \
	   ft_splitf.c \
	   ft_strslen.c \
	   ft_strsfree.c \
	   ft_strupper.c \
	   ft_strlower.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_atof.c \
	   ft_min.c \
	   ft_max.c \
	   ft_isfloatable.c \
	   ft_strlen_until.c \
	   ft_strdup_until.c \
	   ft_fequal.c \
	   ft_flt.c \
	   ft_fgt.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c

BONUSRCS = ft_lstnew.c \
		   ft_lstadd_front.c \
		   ft_lstsize.c \
		   ft_lstlast.c \
		   ft_lstadd_back.c \
		   ft_lstdelone.c \
		   ft_lstclear.c \
		   ft_lstiter.c \
		   ft_lstmap.c

OBJS = $(SRCS:.c=.o)
BONUSOBJS = $(BONUSRCS:.c=.o)

DEPFILES = $(SRCS:.c=.d)
BONUSDEPFILES = $(BONUSRCS:.c=.d)

ifeq ($(MAKECMDGOALS), bonus)
DEPS = $(OBJS) $(BONUSOBJS)
else
DEPS = $(OBJS)
endif

all: $(NAME)

bonus: $(NAME)

$(NAME): $(DEPS)
	ar rcs $@ $^

-include $(DEPFILES) $(BONUSDEPFILES)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
	rm -f *.d
	rm -f get_next_line/*.o
	rm -f get_next_line/*.d

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus