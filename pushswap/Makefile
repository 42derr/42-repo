NAME = push_swap

CHECKER = checker

SRCS = ps_asg.c \
      ps_cmd.c \
      ps_cmd_help.c \
      ps_cmd_helper.c \
      ps_err.c \
      ps_solve.c \
      ps_radix_sort.c \
      ps_radix_utils.c \
      algorithm/iz_main.c \
      algorithm/iz_helper.c \
      algorithm/if_main.c \
      algorithm/if_helper.c \
      algorithm/in_main.c \
      algorithm/ir_main.c \
      algorithm/il_main.c \
      algorithm/il_helper.c \
      libft/ft_atol.c \
      libft/ft_strcmp.c \
      libft/ft_putstr_fd.c \
      bonus/checker.c \
      bonus/checker_help.c \
      bonus/checker_helper.c \
      bonus/get_next_line/get_next_line.c \
      bonus/get_next_line/get_next_line_utils.c \

SRCS_BONUS = bonus/main_checker.c

SRCS_NORMAL = pushswap.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

OBJS_NORMAL = $(SRCS_NORMAL:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(CHECKER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CHECKER): $(OBJS_BONUS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS) -o $(CHECKER)

$(NAME): $(OBJS) $(OBJS_NORMAL)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_NORMAL) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_NORMAL)

fclean: clean
	rm -f $(NAME)
	rm -f $(CHECKER)

re: fclean all

.PHONY: all clean fclean re bonus
