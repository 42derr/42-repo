#ifndef PUSHSWAP_H
# define PUSHSWAP_H

typedef struct s_push
{
    int *stacka;
    int *stackb;
    int asize;
    int bsize;
} t_push;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int     check_argv_helper(int argc , char **argv);
int    check_argv(int argc, char **argv);

int    assign_stacka(int argc, char **argv, t_push *push);
void   reassign_stacka(t_push *push);
int    assign_stackb(int argc, t_push *push);

void   cmd_sa(t_push *push, int p);
void   cmd_sb(t_push *push, int p);
void   cmd_ss(t_push *push);
void   cmd_pa(t_push *push);
void   cmd_pb(t_push *push);
void   cmd_ra(t_push *push, int p);
void   cmd_rb(t_push *push, int p);
void   cmd_rr(t_push *push);
void   cmd_rra(t_push *push, int p);
void   cmd_rrb(t_push *push, int p);
void   cmd_rrr(t_push *push);

void    solve_stack(t_push *push, int argc);
void    solve_stack_3num(t_push *push);
void    solve_stack_4num(t_push *push);
void    solve_stack_5num(t_push *push);

int find_loc(t_push *push, int num);
void    insertion_sort(t_push *push);

# endif