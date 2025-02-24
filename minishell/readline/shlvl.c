/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:04 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:45:05 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_shlvl(char ***envp, int shlvl, int len, t_mini *mini)
{
	char	*shlvl_str;
	char	*new_shlvl;

	shlvl_str = getenv("SHLVL");
	if (!shlvl_str)
		return (0);
	shlvl = ft_atoi(shlvl_str) + 1;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		clean_exit("malloc", mini);
	len = ft_strlen("SHLVL=") + ft_strlen(new_shlvl);
	mini->new_shlvl = (char *) malloc(sizeof(char) * len + 1);
	if (!mini->new_shlvl)
		return (free(new_shlvl), 1);
	ft_memcpy(mini->new_shlvl, "SHLVL=", ft_strlen("SHLVL="));
	ft_memcpy(mini->new_shlvl + ft_strlen("SHLVL="),
		new_shlvl, ft_strlen(new_shlvl) + 1);
	len = 0;
	while ((*envp)[len])
	{
		if (ft_strncmp((*envp)[len], "SHLVL=", 6) == 0)
			return (free(new_shlvl), (*envp)[len] = mini->new_shlvl, 0);
		len++;
	}
	return (free(new_shlvl), 1);
}

char	**make_default_env(void)
{
	char	cwd[PATH_MAX];
	char	*wd;
	char	**envp;

	envp = malloc(sizeof(char *) * 3);
	if (!envp)
		return (perror("envp: "), NULL);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), NULL);
	wd = ft_strdup("PWD=");
	if (!wd)
		return (free(envp), perror("ft_strdup: "), NULL);
	envp[0] = ft_strjoin(wd, cwd);
	free(wd);
	if (!envp[0])
		return (free(envp), perror("ft_strjoin: "), NULL);
	envp[1] = ft_strdup("SHLVL=1");
	if (!envp[1])
	{
		free(envp[0]);
		free(envp);
		return (perror("ft_strdup: "), NULL);
	}
	envp[2] = NULL;
	return (envp);
}
