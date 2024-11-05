#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>   // GNU Readline for input handling
#include <readline/history.h>     // GNU Readline for command history
#include <stdio.h>                // Standard input/output functions
#include <stdlib.h>               // Memory management functions
#include <fcntl.h>                // File control options
#include <unistd.h>               // UNIX standard functions
#include <sys/types.h>           // Data types used in system calls
#include <sys/stat.h>            // File status information
#include <sys/wait.h>            // Waiting for process termination
#include <signal.h>              // Signal handling
#include <string.h>              // String manipulation functions
#include <dirent.h>              // Directory handling
#include <errno.h>               // Error number definitions
#include <sys/ioctl.h>           // Terminal I/O control
#include <termios.h>             // Terminal control definitions
#include <ncurses.h>             // Optional: for advanced terminal control
#include <term.h>                // Optional: for terminal capabilities

typedef enum e_num
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HERE_DOC,
	APPEND,
	PIPE,
	ENV_VAR,
	EXIT_STATUS,
	ARGS,
	AND,
	OR,
	PARENTHESIS,
	WILDCARD,
	END,
	UNKNOWN,
} e_num;

typedef struct s_token
{
	e_num	type;
	char	*value;
}				t_token;

int new_anjing(void);

#endif