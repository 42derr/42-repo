#ifndef PUSHSWAP_H
# define PUSHSWAP_H

typedef struct s_push
{
    int *astart;
    int *bstart;
    char **stacka;
    char **stackb;
    int asize;
    int bsize;
} t_push;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

char    *base4_string(int num);
char    **base4_array(t_push *push);
int     isthere(t_push *push, int num, char c);
int     isthereb(t_push *push, int num, char c);
int     howmany(t_push *push, int num, char c);
int     howmanyb(t_push *push, int num, char c);
int     max_base4(int num);
void    radix_base4(t_push *push);

int base4ToDecimal(char *base4);
int    check_stack_f(t_push *push);
int     istheretwo(t_push *push, int num, char c, int numt, char ct);
int     istherebtwo(t_push *push, int num, char c, int numt, char ct);

void iz_first_zero(t_push *push , int i);
void iz_first_three(t_push *push , int i);
void iz_first(t_push *push, int i);
void iz_second_one(t_push *push , int i);
void iz_second(t_push *push, int i);
void    i_zero(t_push *push, int *i);
int     iz_check_top(t_push *push, int i, int cf, int ct);
int     iz_check_topb(t_push *push, int i, int cf, int ct);
int     iz_check_botb(t_push *push, int i, int cf, int ct);
int     iz_break(t_push *push, int cf, int ct, int is);
int     iz_breakb(t_push *push, int cf, int ct, int is);

void if_zero_helper(t_push *push, int i);
void if_zero(t_push *push, int i);
void    i_first(t_push *push , int i);
int     iz_breakb(t_push *push, int cf, int ct, int is);
void if_three_two(t_push *push , int i);
void if_three(t_push *push , int i);
void if_two(t_push *push, int i);
void if_one_helper(t_push *push, int i);
void if_one(t_push *push, int i);

void fix_loop(t_push *push, int o);
void i_normal_zo_z(t_push *push, int i, int *o);
void i_normal_zo(t_push *push, int i);
void i_normal(t_push *push, int i);

void fix_loop_return(t_push *push, int o);
void i_return_spes(t_push *push, int i, int *o);
void i_return(t_push *push, int i, int max);

void ils_start(t_push *push , int i, int *hun);
void ils_one(t_push *push , int i, int *hun, int max);
void ils_zero(t_push *push , int i, int *o);
void ils_adjust(t_push *push , int o, int hun);
void ils_finish(t_push *push, int i);
void i_last_spes(t_push *push, int i, int max);

# endif