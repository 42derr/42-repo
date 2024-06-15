NAME = push_swap

SRCS = ps_asg.c \
      ps_cmd.c \
      ps_err.c \
      ps_solve.c \
      ps_radix_sort.c \
      ps_radix_utils.c \
      pushswap.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
