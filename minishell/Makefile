CC = cc

# CFLAGS_NORMAL = -Wall -Wextra -Werror

NAME = minishell

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = minishell.c \
			  lexical.c \
			  split_input.c \
			  signal_handler.c \
			  parsing.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -lreadline -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS_NORMAL) -c $< -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
