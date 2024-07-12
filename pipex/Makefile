NAME = pipex

SRCS = pipex.c \
	   pipex_utils.c \
	   pipex_helper.c \
	   libft/ft_strdup.c \
	   libft/ft_split.c \
	   libft/ft_strjoin.c \
	   libft/ft_strnstr.c \
	   libft/ft_strlen.c \
	   libft/ft_strcpy.c \
	   libft/ft_strchr.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_strcmp.c \
	   libft/ft_strncmp.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

bonus: ${NAME}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
