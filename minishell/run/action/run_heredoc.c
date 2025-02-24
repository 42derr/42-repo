/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:00:34 by aputri-a          #+#    #+#             */
/*   Updated: 2024/12/16 07:46:16 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_heredoc(int hdfd_loc, char *limiter, t_mini *mini)
{
	int		expand;
	int		hd_fd;

	hd_fd = mini->hd[hdfd_loc];
	expand = check_hd_expand(limiter);
	if (expand == 1)
		expand_heredoc(mini, &hd_fd, hdfd_loc);
	if (dup2(hd_fd, 0) == -1)
		clean_exit("dup2", mini);
	close(hd_fd);
	mini->hd[hdfd_loc] = 0;
	return (0);
}

void	expand_heredoc(t_mini *mini, int *hd_fd, int hdfd_loc)
{
	int		pfd[2];
	char	*expansion;
	char	buffer[1024];

	ft_memset(buffer, 0, 1024);
	if (pipe(pfd) == -1)
		clean_exit("pipe", mini);
	while (1)
	{
		if (read((*hd_fd), buffer, sizeof(buffer)) < 1)
			break ;
		if (ft_strchr(buffer, '$') == NULL)
			ft_putstr_fd(buffer, pfd[1]);
		else
		{
			expansion = expand_env(buffer, mini, 0, 0);
			ft_putstr_fd(expansion, pfd[1]);
			free(expansion);
		}
	}
	close(pfd[1]);
	close((*hd_fd));
	mini->hd[hdfd_loc] = pfd[0];
	(*hd_fd) = pfd[0];
}

int	check_hd_expand(char *limiter)
{
	int		i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
