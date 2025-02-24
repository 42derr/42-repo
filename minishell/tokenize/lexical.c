/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:42:50 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:42:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenization(char *arg, t_mini *mini)
{
	char	**input;
	t_token	*token_buffer;

	input = cmds_handler(arg);
	if (!input)
		clean_exit("malloc", mini);
	mini->all_input = input;
	token_buffer = add_token(input);
	if (!token_buffer)
		clean_exit("malloc", mini);
	return (token_buffer);
}
