#ifndef MINISHELL_H
# define MINISHELL_H

//idk what is this but it fix sa error
#define _XOPEN_SOURCE 700
#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <signal.h>
#include <string.h>       
#include <dirent.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>      
#include <ncurses.h>
#include <term.h>


typedef enum e_num
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HERE_DOC,
	APPEND,
	PIPE,
	EXIT_STATUS,
	ENV_VAR,
	AND,
	OR,
	PARENTHESIS,
	WILDCARD,
	ARGS,
} e_num;

typedef struct s_token
{
	e_num			type;
	char			*value;
}				t_token;

// from minishell.c
int new_line(void);

// split_input.c
char	*fill_cmd(char **arg, int sq, int dq, int cb);
char	**cmds_handler(char *arg);

//																			signal_handler.c
void handle_sigint(int sig) ;
int new_line(void);

// lexical.c
e_num   get_token_type(char *value);
t_token *get_token(char *cmds);
t_token	*add_token(char **input);
t_token  *tokenization(char *arg);

// from parsing.c
void    parsing(t_token *token_buffer);
void   angel_helper(int num);

#endif