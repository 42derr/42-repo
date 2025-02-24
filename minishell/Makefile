CC = cc

CFLAGS_NORMAL = -Wall -Wextra -Werror -g

NAME = minishell

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = minishell.c \
			readline/read_input.c \
			readline/read_wd.c \
			readline/hd_input.c \
			readline/shlvl.c \
			readline/signal_handler.c \
			readline/init.c \
			readline/terminal.c \
			readline/hd_sigc.c \
			tokenize/lexical.c \
			tokenize/token_cmds.c \
			tokenize/token_csize.c \
			tokenize/token_list.c \
			tokenize/wildcard.c \
			syntax/syntax.c \
			syntax/syn_add_parens.c \
			syntax/syn_cases.c \
			syntax/syn_helper.c \
			syntax/syn_token_check.c \
			parsing/parsing.c \
			parsing/ast_cmd_node.c \
			parsing/ast_helper.c \
			parsing/ast_parens_node.c \
			run/execute.c \
			run/execute_cmds.c \
			run/execute_opr.c \
			run/run_cmds.c \
			run/run_pipe.c \
			run/run_path.c \
			run/utils_mini.c \
			run/utils_execute.c \
			run/action/run_action.c \
			run/action/run_redirect.c\
			run/action/run_heredoc.c \
			run/builtin/run_builtin.c \
			run/builtin/run_cd.c \
			run/builtin/run_echo.c \
			run/builtin/run_env.c \
			run/builtin/run_env_help.c \
			run/builtin/utils_random.c \
			run/builtin/run_exit.c \
			run/builtin/run_export.c \
			run/builtin/run_pwd.c \
			run/builtin/run_temp_env.c \
			run/builtin/run_unset.c \
			run/builtin/utils_builtin.c \
			run/builtin/utils_env.c \
			run/builtin/utils_export.c \
			run/builtin/utils_export_syn.c \
			exit_mini/exit_buildin.c \
			exit_mini/free_iteration.c \
			exit_mini/free_exit.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

bonus: $(NAME)

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

.PHONY: all clean fclean re bonus
