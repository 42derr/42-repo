#include "pipex.h"

void exec_cmd(char *cmd, char **env, t_pipex *pipex)
{
    char **args = ft_split(cmd, ' ');
    char *command = args[0];
    char *full_path;

    if (ft_strchr(command, '/') != NULL)
    {
        if (access(command, X_OK) == 0)
            full_path = command;
        else
            error_handler("access", pipex);
    }
    else
        full_path = find_full_path(command, env, pipex);
    if (!full_path)
    {
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": Command not found\n", 2);
        exit(127);
    }
    if (execve(full_path, args, env) == -1)
        error_handler("execve", pipex);
    free_array(args);
}

int asg_cmd(t_pipex *pipex, int argc, char **argv)
{
    int max;
    int i;
    char **cmd;

    cmd = (char **) malloc (sizeof(char *) * (argc - 2));
    if (!cmd)
        return (0);
    i = 2;
    max = argc - 1;
    pipex->file1 = ft_strdup(argv[1]);
    pipex->file2 = ft_strdup(argv[max]);
    while (i < max)
    {
        cmd[i - 2] = ft_strdup(argv[i]);
        i++;
    }
    cmd[i - 2] = 0;
    pipex->cmd = cmd;
    return (1);
}

void pipe_child(t_pipex *pipex, int *fd ,char **env)
{
    int openfd;

    close (fd[0]);
    if (dup2(fd[1],STDOUT_FILENO) == -1)
        error_handler("dup2", pipex);
    close (fd[1]);
    openfd = open(pipex->file1, O_RDONLY);
    if (openfd == -1)
        error_handler("open", pipex);
    if (dup2(openfd,STDIN_FILENO) == -1)
        error_handler("dup2", pipex);
    close (openfd);
    exec_cmd(pipex->cmd[0], env,pipex);
}

void pipe_parent (t_pipex *pipex, int *fd ,char **env)
{
        int pid2;
        int closefd;

        pid2 = fork();
        if (pid2 == -1)
            error_handler("fork", pipex);
        if (pid2 == 0)
        {
            close(fd[1]);
            closefd = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            if (closefd == -1)
                error_handler("open", pipex);
            if (dup2(fd[0],STDIN_FILENO) == -1)
                error_handler("dup2", pipex);
            if (dup2(closefd,STDOUT_FILENO) == -1)
                error_handler("dup2", pipex);
            close(closefd);
            close(fd[0]);
            exec_cmd(pipex->cmd[1], env, pipex);
        }
        else      
            pipe_exit(pipex, fd, pid2);
}

int main(int argc, char **argv, char **env)
{
    t_pipex pipex;
    int fd[2];
    int pid;

    if (argc != 5)
	    return (1);
    if (!asg_cmd(&pipex, argc, argv))
        return (0);
    if (pipe(fd) == -1)
    {
        perror("pipe");
        free_pipex(&pipex);
        return (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free_pipex(&pipex);
        return (1);
    }
    if (pid == 0)
        pipe_child(&pipex, fd, env);
    else
        pipe_parent(&pipex, fd, env);
    free_pipex(&pipex);
    return (0);
}

