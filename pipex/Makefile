NAME = pipex

NAME_BONUS = relink

SRCS = libft/ft_strdup.c \
	   libft/ft_split.c \
	   libft/ft_strjoin.c \
	   libft/ft_strnstr.c \
	   libft/ft_strlen.c \
	   libft/ft_strcpy.c \
	   libft/ft_memcmp.c \
	   libft/ft_strchr.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_strcmp.c \
	   libft/ft_strncmp.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \

SRCS_NORMAL = pipex.c \
			  pipex_one.c \
	   		  pipex_two.c \
	   		  pipex_three.c \

SRCS_BONUS =  pipex_bonus/pipex_bonus.c \
			  pipex_bonus/pipex_one_bonus.c \
	   		  pipex_bonus/pipex_two_bonus.c \
	   		  pipex_bonus/pipex_three_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

OBJS_NORMAL = $(SRCS_NORMAL:.c=.o)

CC = cc

CFLAGS_BONUS = -Wall -Wextra -Werror -I./pipex_bonus

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(OBJS)
	$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) $(OBJS) -o $(NAME)
	touch $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_NORMAL)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_NORMAL) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_NORMAL) $(NAME_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
