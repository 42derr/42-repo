/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:42 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 00:35:11 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hd_input(t_mini *mini)
{
	int	i;
	int	j;
	int	save;

	if (mini->syn.heredoc == 0)
		return (0);
	mini->sigc = 0;
	save = g_my_signal;
	g_my_signal = 0;
	mini->hd = ft_calloc(mini->syn.heredoc, sizeof(int));
	if (!mini->hd)
		clean_exit("malloc", mini);
	i = 0;
	j = 0;
	while (i < mini->syn.heredoc)
	{
		signal(SIGINT, cmds_sigint);
		while (mini->all_token[j].type != HERE_DOC)
			j++;
		get_hd_input(mini, mini->all_token[++j].value, &mini->hd[i]);
		mini->all_token[j].hd = i;
		i++;
	}
	return (g_my_signal = save, mini->sigc);
}

void	get_hd_input(t_mini *mini, char *limiter, int *fd_buffer)
{
	int		pfd[2];
	int		status;
	pid_t	child_pid;

	if (pipe(pfd) == -1)
		clean_exit("pipe", mini);
	disable_echo(mini);
	child_pid = fork();
	if (child_pid == -1)
	{
		restore_terminal(mini);
		clean_exit("fork", mini);
	}
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		hd_setup(mini, limiter, pfd);
	}
	signal(SIGINT, heredoc_cmds_sigint);
	waitpid(child_pid, &status, 0);
	restore_terminal(mini);
	here_doc_sigc(mini, child_pid);
	close(pfd[1]);
	(*fd_buffer) = pfd[0];
}

void	hd_setup(t_mini *mini, char *limiter, int pfd[2])
{
	int		save_exit;

	close(pfd[0]);
	limiter = ft_trim_quoted(limiter, 0, 0, mini);
	mini->temp_str = limiter;
	while (1)
	{
		save_exit = hd_read(mini, limiter, pfd[1]);
		if (save_exit == 0)
			break ;
	}
	mini->temp_str = NULL;
	free(limiter);
	close(pfd[1]);
	clean_noexit(mini);
	exit(save_exit);
}

char	*here_doc_gnl(void)
{
	char	*str;

	ft_putstr_fd("> ", 0);
	str = get_next_line(0);
	if (!str)
		return (printf("\n"), NULL);
	else
		return (str);
}

int	hd_read(t_mini *mini, char *limiter, int pfd)
{
	char	*input;

	input = here_doc_gnl();
	if (input == NULL)
	{
		ft_print_errs("heredoc: warning: delimited by",
			" end-of-file (wanted `", limiter, "')");
		return (0);
	}
	mini->temp_input = input;
	if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0
		&& (*(input + ft_strlen(limiter)) == '\0'
			|| *(input + ft_strlen(limiter)) == '\n'))
		return (mini->temp_input = NULL, free(input), 0);
	ft_putstr_fd(input, pfd);
	mini->temp_input = NULL;
	return (free(input), 1);
}
