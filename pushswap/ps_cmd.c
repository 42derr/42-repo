#include "pushswap.h"

void   cmd_sa(t_push *push , int p)
{
   char *temp;
   
   if (push->asize < 2)
      return ;
   temp = push->stackaa[push->asize - 1];
   push->stackaa[push->asize - 1] = push->stackaa[push->asize - 2];
   push->stackaa[push->asize - 2] = temp;
   if (p)
      printf("sa\n");
}

void   cmd_sb(t_push *push, int p)
{
   char *temp;
   
   if (push->bsize < 2)
      return ;
   temp = push->stackbb[push->bsize - 1];
   push->stackbb[push->bsize - 1] = push->stackbb[push->bsize - 2];
   push->stackbb[push->bsize - 2] = temp;
   if (p)
      printf("sb\n");
}

void   cmd_ss(t_push *push)
{
   cmd_sa(push, 0);
   cmd_sb(push, 0);
   printf("ss\n");
}

void   cmd_pa(t_push *push)
{   
   if (push->bsize < 1)
      return ;
   push->stackaa[push->asize] = push->stackbb[push->bsize - 1];
   push->stackbb[push->bsize - 1] = 0;
   push->asize = push->asize + 1;
   push->bsize = push->bsize - 1;
   printf("pa\n");
}

void   cmd_pb(t_push *push)
{   
   if (push->asize < 1)
      return ;
   push->stackbb[push->bsize] = push->stackaa[push->asize - 1];
   push->stackaa[push->asize - 1] = 0;
   push->bsize++;
   push->asize--;
   printf("pb\n");
}

void   cmd_ra(t_push *push, int p)
{
   char *temp;
   int i;

   if (push->asize < 1)
      return ;
   i = push->asize - 1;
   temp = push->stackaa[i];
   while (i > 0)
   {
      push->stackaa[i] = push->stackaa[i - 1];
      i--;
   }
   push->stackaa[0] = temp;
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
   temp = push->stackbb[i];
   while (i)
   {
      push->stackbb[i] = push->stackbb[i - 1];
      i--;
   }
   push->stackbb[0] = temp;
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
   temp = push->stackaa[0];
   while (i < push->asize - 1)
   {
      push->stackaa[i] = push->stackaa[i + 1];
      i++;
   }
   push->stackaa[push->asize - 1] = temp;
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
   temp = push->stackbb[0];
   while (i < push->bsize - 1)
   {
      push->stackbb[i] = push->stackbb[i + 1];
      i++;
   }
   push->stackbb[push->bsize - 1] = temp;
   if (p)
      printf("rrb\n");
}

void   cmd_rrr(t_push *push)
{
   cmd_rra(push, 0);
   cmd_rrb(push, 0);
   printf("rrr\n");
}
//333 420 339 790 335 963 579 274 362 694 229 128 404 710 143 22 37 708 214