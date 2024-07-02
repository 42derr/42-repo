NAME = push_swap

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
      pushswap.c

SRCS_BONUS = bonus/get_next_line/get_next_line.c \
             bonus/get_next_line/get_next_line_utils.c \
             bonus/checker.c \
             bonus/checker_help.c \
             bonus/checker_helper.c \
             bonus/main_checker.c \
             libft/ft_atol.c \
             libft/ft_putstr_fd.c \
             libft/ft_strcmp.c \
             ps_err.c \
             ps_asg.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS_BONUS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o checker

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o push_swap

clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(NAME)

fclean: clean
	$(RM) push_swap
	$(RM) checker

re: fclean all

.PHONY: all clean fclean re bonus
