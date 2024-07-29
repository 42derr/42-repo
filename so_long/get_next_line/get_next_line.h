/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/29 18:51:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../llist.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		search_newline(t_list *list);
int		string_length(t_list *list);
char	*string_malloc(t_list *list, char *str, int len);
void	clear_node(t_list **lst);
int		save_string(t_list **list);
char	*create_string(t_list **list, int fd);
char	*get_next_line(int fd);
char	*create_string_helper(t_list **list);
int		addback_new_node(t_list **lst, char **content);
int		save_string_helper(int i, int j, char *content, t_list **list);

#endif
