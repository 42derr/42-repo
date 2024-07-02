#include "pushswap.h"

void   cmd_sa(t_push *push , int p)
{
   char *temp;
   
   if (push->asize < 2)
      return ;
   temp = push->stacka[push->asize - 1];
   push->stacka[push->asize - 1] = push->stacka[push->asize - 2];
   push->stacka[push->asize - 2] = temp;
   if (p)
      ft_putstr_fd("sa\n",1);
}

void   cmd_sb(t_push *push, int p)
{
   char *temp;
   
   if (push->bsize < 2)
      return ;
   temp = push->stackb[push->bsize - 1];
   push->stackb[push->bsize - 1] = push->stackb[push->bsize - 2];
   push->stackb[push->bsize - 2] = temp;
   if (p)
      ft_putstr_fd("sb\n",1);
}

void   cmd_ss(t_push *push)
{
   cmd_sa(push, 0);
   cmd_sb(push, 0);
   ft_putstr_fd("ss\n",1);
}

void   cmd_pa(t_push *push)
{
   if (push->bsize < 1)
      return ;
   push->stacka[push->asize] = push->stackb[push->bsize - 1];
   push->stackb[push->bsize - 1] = 0;
   push->asize = push->asize + 1;
   push->bsize = push->bsize - 1;
   ft_putstr_fd("pa\n",1);
}

void   cmd_pb(t_push *push)
{
   if (push->asize < 1)
      return ;
   push->stackb[push->bsize] = push->stacka[push->asize - 1];
   push->stacka[push->asize - 1] = 0;
   push->bsize++;
   push->asize--;
   ft_putstr_fd("pb\n",1);
}


