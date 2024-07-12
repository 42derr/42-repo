#include "pipex.h"

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

void error_handler(char *err, t_pipex *pipex)
{
    free_pipex(pipex);
    perror(err);
    exit (1);
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

void pipe_exit(t_pipex *pipex, int *fd, int pid2)
{
    int  status;

    status = 0;
    close(fd[0]);
    close(fd[1]);
    if (waitpid(pid2, &status, 0) == -1)
        error_handler("waitpid", pipex);
    // if (waitpid(pid, &status, 0) == -1)
    //     error_handler("waitpid", pipex);
    free_pipex(pipex);
    exit(status >> 8);
}


