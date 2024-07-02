#include "../pushswap.h"

void   checker_ra(t_push *push)
{
   int temp;
   int i;

   if (push->asize < 1)
      return ;
   i = push->asize - 1;
   temp = push->astart[i];
   while (i > 0)
   {
      push->astart[i] = push->astart[i - 1];
      i--;
   }
   push->astart[0] = temp;
}

void   checker_rb(t_push *push)
{
   int temp;
   int i;

   if (push->bsize < 1)
      return ;
   i = push->bsize - 1;
   temp = push->bstart[i];
   while (i > 0)
   {
      push->bstart[i] = push->bstart[i - 1];
      i--;
   }
   push->bstart[0] = temp;
}

void   checker_rr(t_push *push)
{
   checker_ra(push);
   checker_rb(push);
}

void   checker_rra(t_push *push)
{
   int temp;
   int i;

   if (push->asize < 1)
      return ;
   i = 0;
   temp = push->astart[0];
   while (i < push->asize - 1)
   {
      push->astart[i] = push->astart[i + 1];
      i++;
   }
   push->astart[push->asize - 1] = temp;
}

void   checker_rrb(t_push *push)
{
   int temp;
   int i;

   if (push->bsize < 1)
      return ;
   i = 0;
   temp = push->bstart[0];
   while (i < push->bsize - 1)
   {
      push->bstart[i] = push->bstart[i + 1];
      i++;
   }
   push->bstart[push->bsize - 1] = temp;
}