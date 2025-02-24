/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:42:29 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:20:09 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h> 
# include <signal.h>
# include <string.h>       
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>      
# include <ncurses.h>
# include <term.h>
# include <limits.h>

extern volatile sig_atomic_t	g_my_signal;

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

typedef enum e_num
{
	AND,
	OR,
	PIPE,
	BACKGROUND,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	PARENTHESIS,
	FORCED_OUTPUT,
	FD_DUP,
	INPUT_SUBSTITUTE,
	OUTPUT_SUBSTITUTE,
	HERE_STRING,
	REDIRECT_IO,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	APPEND,
	HERE_DOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	BACKTICK,
	EXIT_STATUS,
	ENV_VAR,
	WILDCARD,
	CMDS,
	ARGS,
}	t_num;

typedef struct s_token
{
	t_num		type;
	char		*value;
	char		**wild;
	int			hd;
	int			hd_expand;
}	t_token;

typedef struct s_node
{
	t_token			*token;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*action;
}	t_node;

typedef struct s_parenthesis
{
	int						open;
	int						close;
	struct s_parenthesis	*next;
}	t_parenthesis;

typedef struct s_syntax
{
	t_parenthesis	*parenthesis_info;
	t_token			current;
	t_token			prev;
	int				i;
	int				heredoc;
	int				backtick;
	int				background;
	int				forced_output;
	int				fd_dup;
	int				here_string;
	int				input_sub;
	int				output_sub;
	int				parenthesis;
	int				msg;
	int				sq;
	int				dq;
	int				bt;
}	t_syntax;

typedef struct s_mini
{
	t_list			*temp_env;
	t_node			*all_node;
	t_token			*all_token;
	t_syntax		syn;
	pid_t			left;
	pid_t			right;
	char			**cmds;
	char			**temp_arr;
	char			**export_envp;
	char			**envp;
	char			**all_input;
	char			*input;
	char			*temp_str;
	char			*temp_input;
	char			*exit_temp;
	char			*cwd;
	char			*new_shlvl;
	int				*hd;
	int				stdout;
	int				stdin;
	int				exit;
	int				exit_status;
	int				exit_max;
	int				temp;
	int				sigc;
	struct termios	orig_termios;
}	t_mini;

// -------------- READLINE -------------- //

// from read_input.c
int		new_line(char ***envp, t_mini *mini);
int		check_whitespace(char *str);
void	dup_back(t_mini *mini);

// from read_wd.c
char	*alter_working_dir(void);
int		alter_wd_helper(int max, char **full_path, int i, char **path);
int		set_full_path(int max, char **path, char **full_path, int *i);

// from hd_input.c
int		hd_input(t_mini *mini);
void	get_hd_input(t_mini *mini, char *limiter, int *fd_buffer);
void	hd_setup(t_mini *mini, char *limiter, int pfd[2]);
char	*here_doc_gnl(void);
int		hd_read(t_mini *mini, char *limiter, int pfd);

// from shlvl.c
int		update_shlvl(char ***envp, int shlvl, int len, t_mini *mini);
char	**make_default_env(void);

// from signal_handler.c
void	handle_sigint(int sig);
void	cmds_sigint(int sig);
void	cmds_sigquit(int sig);
void	heredoc_cmds_sigint(int sig);

// from init.c
void	init_mini(t_mini *mini, char ***envp);
char	**init_envp(char **envp);

// from terminal.c
void	disable_echo(t_mini *mini);
void	restore_terminal(t_mini *mini);

// from hd_sigc.c
void	here_doc_sigc(t_mini *mini, pid_t child_pid);

// -------------- TOKENIZE -------------- //

// from lexical.c
t_token	*tokenization(char *arg, t_mini *mini);

// from token_cmds.c
char	**cmds_handler(char *arg);
char	*fill_cmd(char **arg, int sq, int dq, int bt);
int		find_cmd_token(char **arg);
void	cmd_quote_check(char **arg, int *sq, int *dq, int *bt);

// from token_csize.c
int		get_cmd_array_size(char *arg);
int		get_cmd_size(char **arg, int sq, int dq, int bt);

// from token_list.c
t_token	*add_token(char **input);
int		get_token(char *cmds, t_token *new_token);
t_num	get_token_type(char *value);
t_num	get_token_type_cont(char *value);

// from wildcard.c
char	**get_wildcard(char *value, int i);
int		match_wildcard(char *pattern, char *str);
int		get_wildcard_size(char *value);
int		read_dir_wildcard(DIR *dir, char *value, char ***args, int i);

// -------------- SYNTAX -------------- //

// from syntax.c
int		syntax_check(t_mini *mini);
int		syntax_end(t_mini *mini);

// from syn_add_parens.c
void	open_parenthesis(t_mini *mini);
void	close_parenthesis(t_mini *mini);

// from syn_cases.c
int		syntax_open_parenthesis(t_mini *mini);
int		syntax_close_parenthesis(t_mini *mini);
int		syntax_operators_redirects_end(t_mini *mini);
int		syntax_pair_check(t_mini *mini, char *arg);
int		syntax_arithmetic_check(t_mini *mini);

// from syn_helper.c
void	update_next_token(t_mini *mini);
int		syntax_cmd_after_paren(t_mini *mini);
void	syntax_msg(t_mini *mini, char *msg);
void	unexpected_token_msg(t_mini *mini);
int		unsupported_msg(t_mini *mini);

// from syn_token_check.c
int		token_is_open_parenthesis(t_token token, t_mini *mini);
int		token_is_operator(t_token token, t_mini *mini);
int		token_is_redirect(t_token token, t_mini *mini);
int		token_is_cmd(t_token token, t_mini *mini);
void	unsupported_check(t_token token, t_mini *mini);

// -------------- PARSING -------------- //

// from parsing.c
void	parsing(t_mini *mini);
t_node	*parse_input(t_token *token_buffer, int start, int end, t_mini *mini);

// from ast_cmd_node.c
t_node	*new_command_node(t_token *token_buffer, int start,
			int end, t_mini *mini);
t_node	*new_action_node(t_token *token_buffer, int start,
			int end, t_mini *mini);
t_node	*new_args_node(t_token *token_buffer, int start,
			int end, t_mini *mini);

// from ast_helper.c
t_node	*create_node(t_mini *mini);
void	skip_through_parenthesis(t_token *token_buffer, int start,
			int end, int *i);
int		get_next_root(t_token *token_buffer, int start, int end);
int		get_next_action(t_token *token_buffer, int start, int end);
int		is_this_operator(int num);

// from ast_parens_node.c
t_node	*new_parenthesis_node(t_token *token_buffer, int start,
			int end, t_mini *mini);
t_token	*create_parenthesis_token(t_mini *mini);

// -------------- RUN -------------- //

// from execute.c
int		execute(t_node *final, char ***envp, t_mini *mini);

// from execute_cmds.c
int		execute_cmds(t_node *node, t_mini *mini);
int		execute_parenthesis(t_node *node, char ***envp, t_mini *mini);

// from execute_opr.c
int		execute_or(t_node *node, char ***envp, t_mini *mini);
int		execute_and(t_node *node, char ***envp, t_mini *mini);
int		execute_pipe(t_node *node, char ***envp, t_mini *mini);

// from run_cmds.c
int		run_command(char **args, t_mini *mini, t_node *node);
void	exec_cmd(char **args, t_mini *mini);
void	clean_fd(t_mini *mini);
void	handle_not_found(char *str, t_mini *mini);

// from run_path.c
char	*find_full_path(char *command, t_mini *mini);
char	*path_handler(char ***dir, char *command);
char	*final_path(char *dir, char *cmd);

// from run_pipe.c
pid_t	create_pipe(t_node *node, char ***envp, t_mini *mini, int direc);
void	create_fork(pid_t *child, int pfd[2], t_mini *mini);

// from utils_execute.c
char	**cmds_array(t_node *final, t_mini *mini);
void	cmds_array_helper(char ***args, int *i, t_node *store, t_mini *mini);
void	cmds_array_setter(char ***args, int *i, t_node *store, t_mini *mini);
void	run_command_status(int status, t_mini *mini, pid_t child);
void	expand_array(t_node *store, t_mini *mini, char ***args, int *i);

// from utils_mini.c
void	free_array_exit(char ***arr, t_mini *mini);
void	free_str_exit(char **str, t_mini *mini);
int		get_num_command(t_node *final, t_mini *mini);
int		count_spaces(char *str, t_mini *mini);

// -------------- RUN/ACTION -------------- //

// from run_action.c
int		run_action(t_mini *mini, t_node *node, int expand);
int		handle_filename_expand(char **expansion, t_node *node,
			t_mini *mini, int *expand);
int		handle_wildcard_redirect(char **filename, t_node *node);

// from run_redirect.c
int		run_redirect_input(char **file, int expand, t_mini *mini);
int		run_redirect_output(char **file, int expand, t_mini *mini);
int		run_append(char **file, int expand, t_mini *mini);
int		run_redirect_io(char **file, int expand, t_mini *mini);
int		handle_fail_open(int fd, char **file, int expand);

// from run_heredoc.c
int		run_heredoc(int hd_fd, char *limiter, t_mini *mini);
void	expand_heredoc(t_mini *mini, int *hd_fd, int hdfd_loc);
int		check_hd_expand(char *limiter);

// -------------- RUN/BUILTIN -------------- //

// from run_builtin
void	run_builtin(char **args, t_mini *mini);

// from run_cd.c
int		run_cd(char **dir, t_mini *mini, int i);

// from run_echo.c
int		run_echo(char **dir);
int		echo_newline(char *str);

// from run_env.c
int		run_env(char **dir, t_mini *mini);
void	sync_env(char *new_str, t_mini *mini);
void	edit_env(char *new_str, t_mini *mini);
char	*get_env_smart(char *str, t_mini *mini, int i, int len);
char	*mygetenv(char **name, t_mini *mini);

// from run_exit.c
int		run_exit(char **dir, t_mini *mini);
long	ft_atol_spes(char *nptr, t_mini *mini);
int		is_number(char *str);
int		call_run_exit(char **dir, t_mini *mini);

// from run_export.c
int		run_export(char **dir, t_mini *mini);
void	print_export_env(t_mini *mini, int type);
void	sort_export(char ***env);
char	*fix_syntax_string(char *str);
char	**fix_syntax(char **env);

// from run_pwd.c
int		run_pwd(void);

// from run_temp_env.c
void	handle_temp_env(char *str, t_mini *mini);
void	handle_temp_env_helper(char *str, t_mini *mini, char **new);
int		check_temp_env(char *new_str, t_mini *mini, char ***temp, int i);
char	*search_temp(char **str, t_mini *mini);
void	handle_old_temp(char **new, t_mini *mini, char **old, char *str);

// from run_unset.c
int		run_unset(char **dir, t_mini *mini);
void	unset_export_env(char *new_str, t_mini *mini);
void	unset_real_env(char *new_str, t_mini *mini);
void	unset_temp_env(char *str, t_mini *mini);

// from utils_builtin.c
int		build_in_handler(char **args, t_mini *mini, t_node *node);
t_node	*build_in_temp(t_node *node, t_mini *mini);
int		check_build_temp(char *str, t_mini *mini);
char	*ft_trim_quoted(char *str, int sq, int dq, t_mini *mini);

// from utils_env.c
int		get_env_smart_check(int c);
int		get_env_check(int c, int cn, int sq, int dq);
int		get_env_len(char *str, t_mini *mini, int sq, int dq);
char	*expand_env(char *str, t_mini *mini, int sq, int dq);
void	expand_env_helper(char *str, int *i, t_mini *mini, char **env_string);

// from utils_export.c
int		append_export(char *new_str, t_mini *mini, int i);
int		edit_export(char *new_str, char **old_str, t_mini *mini);
int		check_duplicate(char *new_str, t_mini *mini);
int		is_in_export(char *str, t_mini *mini);
void	dup_export(char **env, char ***temp, int *i, t_mini *mini);

// from utils_export_syn.c
int		syntax_new(char *str);
char	*fix_syntax_new(char *str, t_mini *mini);
void	fix_syntax_help(char *str, char **new, int i, int j);
void	single_double(char *str, int i, int *sq, int *dq);

// from run_env_help.c
char	*env_exit_stat(char *str, int len, t_mini *mini);

// from utils_random.c
void	malloc_expand(char **new_str, char *str, t_mini *mini);
void	ft_print_errs(char *stra, char *strb, char *strc, char *strd);
void	run_command_status(int status, t_mini *mini, pid_t child);

// -------------- EXIT -------------- //

// from exit_buldin.c
void	exit_minishell(t_mini *mini);

// from free_exit.c
void	free_all_node(t_node *node);
void	free_syntax(t_mini *mini);
void	free_wild_card(t_mini *mini);
void	free_syntax_hd(t_mini *mini);
void	free_iteration(t_mini *mini);

// from free_exit.c
void	free_temp(t_mini *mini);
void	clean_noexit(t_mini *mini);
void	clean_exit(char *err, t_mini *mini);

char	*expand_home(t_mini *mini);

#endif
