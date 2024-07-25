/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:17:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 19:32:11 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_push
{
	int		*astart;
	int		*bstart;
	char	**stacka;
	char	**stackb;
	int		asize;
	int		bsize;
}	t_push;

int		check_argv_helper(int argc, char **argv);
int		check_argv(int argc, char **argv);
int		check_stack(t_push *push);

int		assign_stacka(int argc, char **argv, t_push *push);
int		reassign_stacka(t_push *push);
int		assign_stackb(int argc, t_push *push);

void	cmd_sa(t_push *push, int p);
void	cmd_sb(t_push *push, int p);
void	cmd_ss(t_push *push);
void	cmd_pa(t_push *push);
void	cmd_pb(t_push *push);
void	cmd_ra(t_push *push, int p);
void	cmd_rb(t_push *push, int p);
void	cmd_rr(t_push *push);
void	cmd_rra(t_push *push, int p);
void	cmd_rrb(t_push *push, int p);
void	cmd_rrr(t_push *push);

void	solve_stack(t_push *push, int argc);
void	solve_stack_3num(t_push *push);
void	solve_stack_4num(t_push *push);
void	solve_stack_5num(t_push *push);

char	*base4_string(int num);
char	**base4_array(t_push *push);
int		isthere(t_push *push, int num, char c);
int		isthereb(t_push *push, int num, char c);
int		howmany(t_push *push, int num, char c);
int		howmanyb(t_push *push, int num, char c);
int		max_base4(int num);
void	radix_base4(t_push *push);

void	iz_first_zero(t_push *push, int i);
void	iz_first_three(t_push *push, int i);
void	iz_first(t_push *push, int i);
void	iz_second_one(t_push *push, int i);
void	iz_second(t_push *push, int i);
void	i_zero(t_push *push, int *i);
int		iz_check_top(t_push *push, int i, int cf, int ct);
int		iz_check_topb(t_push *push, int i, int cf, int ct);
int		iz_check_botb(t_push *push, int i, int cf, int ct);
int		iz_break(t_push *push, int cf, int ct, int is);
int		iz_breakb(t_push *push, int cf, int ct, int is);

void	if_zero_helper(t_push *push, int i);
void	if_zero(t_push *push, int i);
void	i_first(t_push *push, int i);
int		iz_breakb(t_push *push, int cf, int ct, int is);
void	if_three_two(t_push *push, int i);
void	if_three(t_push *push, int i);
void	if_two(t_push *push, int i);
void	if_one_helper(t_push *push, int i);
void	if_one(t_push *push, int i);

void	fix_loop(t_push *push, int o);
void	i_normal_zo_z(t_push *push, int i, int *o);
void	i_normal_zo(t_push *push, int i);
void	i_normal(t_push *push, int i);

void	fix_loop_return(t_push *push, int o);
void	i_return_spes(t_push *push, int i, int *o);
void	i_return(t_push *push, int i, int max);

void	ils_start(t_push *push, int i, int *hun);
void	ils_one(t_push *push, int i, int *hun, int max);
void	ils_zero(t_push *push, int i, int *o);
void	ils_adjust(t_push *push, int o, int hun);
void	ils_finish(t_push *push, int i);
void	i_last_spes(t_push *push, int i, int max);
void	print_5num(t_push *push);

long	ft_atol(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

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

void	checker_ra(t_push *push);
void	checker_rb(t_push *push);
void	checker_rr(t_push *push);
void	checker_rra(t_push *push);
void	checker_rrb(t_push *push);
void	checker_sa(t_push *push);
void	checker_sb(t_push *push);
void	checker_ss(t_push *push);
void	checker_pa(t_push *push);
void	checker_pb(t_push *push);
void	checker_rrr(t_push *push);

int		do_cmd(char *str, t_push *push);
void	check_sort(t_push *push);
void	free_array(char	**buffer);
void	free_all(t_push *push);
void	stackb_array(t_push *push);
void	cmd_gnl(t_push *push);

#endif
