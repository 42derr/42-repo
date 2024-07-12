#include "pipex.h"

void exec_cmd(char *cmd, char **env, t_pipex *pipex)
{
    char **args;
    char *command;
    char *full_path;

    args = ft_split(cmd, ' ');
    command = args[0];
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
    int i;
    char **cmd;

    cmd = (char **) malloc (sizeof(char *) * (argc));
    if (!cmd)
        return (0);
    if (ft_strcmp(argv[1], "here_doc") == 0)
    {
        pipex->hd = 1;
        argv++;
        argc--;
    }
    i = 2;
    pipex->file1 = ft_strdup(argv[1]);
    pipex->file2 = ft_strdup(argv[argc -1]);
    while (i < argc - 1)
    {
        cmd[i - 2] = ft_strdup(argv[i]);
        i++;
    }
    cmd[i - 2] = 0;
    pipex->cmd = cmd;
    pipex->cmdsize = i - 2;
    return (1);
}

void create_pipe(t_pipex *pipex, char **env, int i, pid_t **pid)
{
    int fd[2];
    int openfd;

    if (pipe(fd) == -1)
        error_handler("pipe", pipex);
    (*pid)[i] = fork();
    if ((*pid)[i] == -1)
        error_handler("fork", pipex);
    if ((*pid)[i] == 0)
    {
        if (i == 0 && !pipex->hd)
        {
            openfd = open(pipex->file1, O_RDONLY);
            if (openfd == -1)
                error_handler("dup2", pipex);
            if (dup2(openfd,STDIN_FILENO) == -1)
                error_handler("dup2", pipex);
            close(openfd);
        }
        close (fd[0]);
        if (dup2(fd[1],STDOUT_FILENO) == -1)
            error_handler("dup2", pipex);
        close (fd[1]);
        exec_cmd(pipex->cmd[i], env,pipex);
    }
    else
    {
        close (fd[1]);
        if (dup2(fd[0],STDIN_FILENO) == -1)
            error_handler("dup2", pipex);
        close (fd[0]);
    }
}

void handle_doc(char *lim, t_pipex *pipex)
{
    char *buffer;
    size_t len;
    int fd[2];
    pid_t pid;

    len = ft_strlen(lim);
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
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
    else
    {
        close (fd[1]);
        if (dup2(fd[0],STDIN_FILENO) == -1)
            error_handler("dup2", pipex);
        close (fd[0]);
    }
}

int main(int argc, char **argv, char **env)
{
    t_pipex pipex;
    int closefd;
    int i;
    pid_t *pid;

    pipex = (t_pipex){0};
    pid = (pid_t *) malloc(sizeof(pid_t) * 10);
    if (!pid)
        return (0);
    if (argc < 5)
	    return (1);
    if (!asg_cmd(&pipex, argc, argv))
        return (0);
    i = 0;
    if (pipex.hd)
        handle_doc(argv[2], &pipex);
    while (i < pipex.cmdsize - 1)
    {
        create_pipe(&pipex, env, i, &pid);
        i++;
    }
    if (ft_strcmp(argv[1], "here_doc") == 0)
    {
        closefd = open(pipex.file2, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (closefd == -1)
            error_handler("open", &pipex);
    }
    else
    {
        closefd = open(pipex.file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (closefd == -1)
            error_handler("open", &pipex);
    }
    if (dup2(closefd,STDOUT_FILENO) == -1)
        error_handler("dup2", &pipex);
    close(closefd);
    exec_cmd(pipex.cmd[pipex.cmdsize - 1], env, &pipex);

    i = 0;
    while (i < pipex.cmdsize -1)
    {
        waitpid(pid[i], NULL, 0);
        i++;
    }
    free(pid);
    free_pipex(&pipex);
    return(0);
}

//8 -> because exit status