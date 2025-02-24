/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:25 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:45:26 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute(t_node *node, char ***envp, t_mini *mini)
{
	if (node == NULL || !node->token)
		return (0);
	if (node->token->type == AND)
		return (execute_and(node, envp, mini));
	else if (node->token->type == OR)
		return (execute_or(node, envp, mini));
	else if (node->token->type == PIPE)
		return (execute_pipe(node, envp, mini));
	else if (node->token->type == CMDS)
		return (execute_cmds(node, mini));
	else if (node->token->type == PARENTHESIS)
		return (execute_parenthesis(node, envp, mini));
	return (0);
}
