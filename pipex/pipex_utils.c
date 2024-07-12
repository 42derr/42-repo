#include "pipex.h"

void doc_child(t_pipex *pipex, int fd[2], char *lim)
{
    char *buffer;
    size_t len;

    len = ft_strlen(lim);
    close (fd[0]);
    if (dup2(fd[1],STDOUT_FILENO) == -1)
        error_handler("dup2", pipex);
    close (fd[1]);
    while (1)
    {
        buffer = get_next_line(0);
        if (ft_strncmp(buffer, lim, len) == 0 && buffer[len] == '\n')
            break;
        ft_putstr_fd(buffer, STDOUT_FILENO);
        free(buffer);
    }
    free(buffer);
    exit(0);
}

void handle_doc(char *lim, t_pipex *pipex)
{
    int fd[2];
    int pid;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        doc_child(pipex, fd, lim);
    }
    else
    {
        close (fd[1]);
        if (dup2(fd[0],STDIN_FILENO) == -1)
            error_handler("dup2", pipex);
        close (fd[0]);
    }
}

void free_pipex(t_pipex *pipex)
{
    int i;

    i = 0;
    free(pipex->file1);
    free(pipex->file2);
    while (pipex->cmd[i])
    {
        free(pipex->cmd[i]);
        i++;
    }
}

void	free_array(char	**buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);

}

void error_handler(char *err, t_pipex *pipex)
{
    free_pipex(pipex);
    perror(err);
    exit (1);
}

