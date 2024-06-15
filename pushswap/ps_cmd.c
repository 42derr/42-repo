#include "pushswap.h"

void   cmd_sa(t_push *push , int p)
{
   t_buffer *temp;
   
   if (push->agroupsize < 2)
      return ;
   temp = push->stackaaa[push->agroupsize - 1];
   push->stackaaa[push->agroupsize - 1] = push->stackaaa[push->agroupsize - 2];
   push->stackaaa[push->agroupsize - 2] = temp;
   if (p)
      printf("sa\n");
}

void   cmd_sb(t_push *push, int p)
{
   t_buffer *temp;
   
   if (push->bgroupsize < 2)
      return ;
   temp = push->stackbbb[push->bgroupsize - 1];
   push->stackbbb[push->bgroupsize - 1] = push->stackbbb[push->bgroupsize - 2];
   push->stackbbb[push->bgroupsize - 2] = temp;
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
   int count;

   if (push->bgroupsize < 1)
      return ;
   push->stackaaa[push->agroupsize] = push->stackbbb[push->bgroupsize - 1];
   count = push->stackaaa[push->agroupsize]->size;
   while (count--)
   {
      printf("pa\n");
   }
   push->stackbbb[push->bgroupsize - 1] = 0;
   push->agroupsize = push->agroupsize + 1;
   push->bgroupsize = push->bgroupsize - 1;
}

void   cmd_pb(t_push *push)
{
   int count;
   if (push->agroupsize < 1)
      return ;
   push->stackbbb[push->bgroupsize] = push->stackaaa[push->agroupsize - 1];
   count = push->stackbbb[push->bgroupsize]->size;
   while (count--)
   {
      printf("pb\n");
   }
   push->stackaaa[push->agroupsize - 1] = 0;
   push->bgroupsize++;
   push->agroupsize--;
}

void   cmd_ra(t_push *push, int p)
{
   t_buffer *temp;
   int i;
   int count;

   if (push->agroupsize < 1)
      return ;

   count = push->stackaaa[push->agroupsize - 1]->size;
   i = push->agroupsize - 1;
   temp = push->stackaaa[i];
   while (i > 0)
   {
      push->stackaaa[i] = push->stackaaa[i - 1];
      i--;
   }
   push->stackaaa[0] = temp;
   while (count--)
   {
      if (p)
         printf("ra\n");
   }
}

void   cmd_rb(t_push *push, int p)
{
   t_buffer *temp;
   int i;
   int count;

   if (push->bgroupsize < 1)
      return ;

   count = push->stackbbb[push->bgroupsize - 1]->size;
   i = push->bgroupsize - 1;
   temp = push->stackbbb[i];
   while (i > 0)
   {
      push->stackbbb[i] = push->stackbbb[i - 1];
      i--;
   }
   push->stackbbb[0] = temp;
   while (count--)
   {
      if (p)
         printf("rb\n");
   }
}

void   cmd_rr(t_push *push)
{
   cmd_ra(push, 0);
   cmd_rb(push, 0);
   printf("rr\n");
}

void   cmd_rra(t_push *push, int p)
{
   t_buffer *temp;
   int i;
   int count;

   if (push->agroupsize < 1)
      return ;
   count = push->stackaaa[0]->size;
   i = 0;
   temp = push->stackaaa[0];
   while (i < push->agroupsize - 1)
   {
      push->stackaaa[i] = push->stackaaa[i + 1];
      i++;
   }
   push->stackaaa[push->agroupsize - 1] = temp;
   while (count--)
   {
      if (p)
         printf("rra\n");
   }
}

void   cmd_rrb(t_push *push, int p)
{
   t_buffer *temp;
   int i;
   int count;

   if (push->bgroupsize < 1)
      return ;
   count = push->stackbbb[0]->size;
   i = 0;
   temp = push->stackbbb[0];
   while (i < push->bgroupsize - 1)
   {
      push->stackbbb[i] = push->stackbbb[i + 1];
      i++;
   }
   push->stackbbb[push->bgroupsize - 1] = temp;
   while (count--)
   {
      if (p)
         printf("rrb\n");
   }
}

void   cmd_rrr(t_push *push)
{
   cmd_rra(push, 0);
   cmd_rrb(push, 0);
   printf("rrr\n");
}
//333 420 339 790 335 963 579 274 362 694 229 128 404 710 143 22 37 708 214