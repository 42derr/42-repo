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
    free(full_path);
    free_array(args);
}

char *final_path(char *dir, char *cmd, t_pipex *pipex) 
{
    char *full_path;
    int dir_len;
    int cmd_len;

    dir_len = (int)ft_strlen(dir);
    cmd_len = (int)ft_strlen(cmd);
    full_path =(char *) malloc(sizeof(char) * (dir_len + cmd_len + 2));
    if (!full_path) 
        error_handler("malloc", pipex);
    ft_strcpy(full_path, dir);
    full_path[dir_len] = '/';
    ft_strcpy(full_path + dir_len + 1, cmd);
    return (full_path);
}

char *find_full_path(char *command, char **env, t_pipex *pipex) 
{
    int i;
    char *path;
    char **dir;

    i = 0;
    while (env[i])
    {
        if (ft_strnstr(env[i], "PATH=", 5) != 0)
            path = ft_strnstr(env[i], "PATH=", 5);
        i++;
    }
    dir = ft_split(path + 5, ':');
    i = 0;
    while (dir[i])
    {
        path = final_path(dir[i++], command, pipex);
        if (access(path, X_OK) == 0) 
        {
            free_array(dir);
            return path;
        }
        free(path);
    }
    free_array(dir);
    return NULL;
}
