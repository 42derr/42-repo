#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h> 

typedef struct s_pipex
{
	char			*file1;
	char			*file2;
	int				hd;
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
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

int		search_newline(t_list *list);
int		string_length(t_list *list);
char	*string_malloc(t_list *list, char *str, int len);
void	clear_node(t_list **lst);
int		save_string(t_list **list);
char	*create_string(t_list **list, int fd);
char	*get_next_line(int fd);
char	*create_string_helper(t_list **list);
int		addback_new_node(t_list **lst, char **content);
int		save_string_helper(int i, int j, char *content, t_list **list);

int asg_cmd(t_pipex *pipex, int argc, char **argv);
void child_pipe(t_pipex *pipex, int fd[2], int i, char **env);
void    proceed_output(t_pipex *pipex, char **env);
void create_pipe(t_pipex *pipex, char **env, int i, pid_t **pid);
void doc_child(t_pipex *pipex, int fd[2], char *lim);
void handle_doc(char *lim, t_pipex *pipex);
void free_pipex(t_pipex *pipex);
void	free_array(char	**buffer);
void error_handler(char *err, t_pipex *pipex);
void exec_cmd(char *cmd, char **env, t_pipex *pipex);
char *final_path(char *dir, char *cmd, t_pipex *pipex);
char *find_full_path(char *command, char **env, t_pipex *pipex);

#endif
