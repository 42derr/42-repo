#include "../pushswap.h"

void   checker_sa(t_push *push)
{
   int temp;
   
   if (push->asize < 2)
      return ;
   temp = push->astart[push->asize - 1];
   push->astart[push->asize - 1] = push->astart[push->asize - 2];
   push->astart[push->asize - 2] = temp;
}

void   checker_sb(t_push *push)
{
   int temp;
   
   if (push->bsize < 2)
      return ;
   temp = push->bstart[push->bsize - 1];
   push->bstart[push->bsize - 1] = push->bstart[push->bsize - 2];
   push->bstart[push->bsize - 2] = temp;
}

void   checker_ss(t_push *push)
{
   checker_sa(push);
   checker_sb(push);
}

void   checker_pa(t_push *push)
{
   if (push->bsize < 1)
      return ;
   push->astart[push->asize] = push->bstart[push->bsize - 1];
   push->bstart[push->bsize - 1] = 0;
   push->asize = push->asize + 1;
   push->bsize = push->bsize - 1;
}

void   checker_pb(t_push *push)
{
   if (push->asize < 1)
      return ;
   push->bstart[push->bsize] = push->astart[push->asize - 1];
   push->astart[push->asize - 1] = 0;
   push->bsize++;
   push->asize--;}


