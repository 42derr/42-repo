NAME = push_swap

SRCS = ps_asg.c \
      ps_cmd/ps_cmd.c \
      ps_cmd/ps_cmd_help.c \
      ps_cmd/ps_cmd_helper.c \
      ps_err.c \
      ps_solve.c \
      ps_radix_sort.c \
      ps_radix_utils.c \
      i_zero/iz_main.c \
      i_zero/iz_helper.c \
      i_zero/if_main.c \
      i_zero/if_helper.c \
      i_normal/in_main.c \
      i_return/ir_main.c \
      i_last/il_main.c \
      i_last/il_helper.c \
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
