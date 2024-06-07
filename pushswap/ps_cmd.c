#include "pushswap.h"

void   cmd_sa(t_push *push , int p)
{
   int temp;
   
   if (push->asize < 2)
      return ;
   temp = push->stacka[push->asize - 1];
   push->stacka[push->asize - 1] = push->stacka[push->asize - 2];
   push->stacka[push->asize - 2] = temp;
   if (p)
      printf("sa\n");
}

void   cmd_sb(t_push *push, int p)
{
   int temp;
   
   if (push->bsize < 2)
      return ;
   temp = push->stackb[push->bsize - 1];
   push->stackb[push->bsize - 1] = push->stackb[push->bsize - 2];
   push->stackb[push->bsize - 2] = temp;
   if (p)
      printf("sb\n");
}

void   cmd_ss(t_push *push)
{
   cmd_sa(push, 0);
   cmd_sb(push, 1);
   printf("ss\n");
}

void   cmd_pa(t_push *push)
{   
   if (push->bsize < 1)
      return ;
   push->stacka[push->asize] = push->stackb[push->bsize - 1];
   push->stackb[push->bsize - 1] = 0;
   push->asize = push->asize + 1;
   push->bsize = push->bsize - 1;
   printf("pa\n");
}

void   cmd_pb(t_push *push)
{   
   if (push->asize < 1)
      return ;
   push->stackb[push->bsize] = push->stacka[push->asize - 1];
   push->stacka[push->asize - 1] = 0;
   push->bsize++;
   push->asize--;
   printf("pb\n");
}

void   cmd_ra(t_push *push, int p)
{
   int temp;
   int i;

   if (push->asize < 1)
      return ;
   i = push->asize - 1;
   temp = push->stacka[i];
   while (i > 0)
   {
      push->stacka[i] = push->stacka[i - 1];
      i--;
   }
   push->stacka[0] = temp;
   if (p)
      printf("ra\n");
}

void   cmd_rb(t_push *push, int p)
{
   int temp;
   int i;

   if (push->bsize < 1)
      return ;
   i = push->bsize - 1;
   temp = push->stackb[i];
   while (i)
   {
      push->stackb[i] = push->stackb[i - 1];
      i--;
   }
   push->stackb[0] = temp;
   if (p)
      printf("rb\n");
}

void   cmd_rr(t_push *push)
{
   cmd_ra(push, 0);
   cmd_rb(push, 0);
   printf("rr\n");
}

void   cmd_rra(t_push *push, int p)
{
   int temp;
   int i;

   if (push->asize < 1)
      return ;
   i = 0;
   temp = push->stacka[0];
   while (i < push->asize - 1)
   {
      push->stacka[i] = push->stacka[i + 1];
      i++;
   }
   push->stacka[push->asize - 1] = temp;
   if (p)
      printf("rra\n");
}

void   cmd_rrb(t_push *push, int p)
{
   int temp;
   int i;

   if (push->bsize < 1)
      return ;
   i = 0;
   temp = push->stackb[0];
   while (i < push->bsize - 1)
   {
      push->stackb[i] = push->stackb[i + 1];
      i++;
   }
   push->stackb[push->bsize - 1] = temp;
   if (p)
      printf("rrb\n");
}

void   cmd_rrr(t_push *push)
{
   cmd_rra(push, 0);
   cmd_rrb(push, 0);
   printf("rrr\n");
}