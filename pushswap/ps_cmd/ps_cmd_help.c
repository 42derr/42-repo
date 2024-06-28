#include "../pushswap.h"

void   cmd_ra(t_push *push, int p)
{
   char *temp;
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
   char *temp;
   int i;

   if (push->bsize < 1)
      return ;
   i = push->bsize - 1;
   temp = push->stackb[i];
   while (i > 0)
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
   char *temp;
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
   char *temp;
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