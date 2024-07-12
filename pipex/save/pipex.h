#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>       // open
#include <unistd.h>      // close, read, write, access, dup, dup2, execve, fork, pipe, unlink
#include <stdlib.h>      // malloc, free, exit
#include <stdio.h>       // perror
#include <string.h>      // strerror
#include <sys/wait.h>    // wait, waitpid

typedef struct s_pipex
{
	char			*file1;
	char			*file2;
	char			**cmd;
	int				cmdsize;
}	t_pipex;

char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);

char *final_path(char *dir, char *cmd, t_pipex *pipex) ;
char *find_full_path(char *command, char **env, t_pipex *pipex) ;
void exec_cmd(char *cmd, char **env, t_pipex *pipex);
int asg_cmd(t_pipex *pipex, int argc, char **argv);
void free_pipex(t_pipex *pipex);
void error_handler(char *err, t_pipex *pipex);
void	free_array(char	**buffer);
void pipe_child(t_pipex *pipex, int *fd ,char **env);
void pipe_parent (t_pipex *pipex, int *fd ,char **env);
void pipe_exit(t_pipex *pipex, int *fd, int pid2);


#endif

//can use wait tho