#include "../pushswap.h"

void   cmd_rrr(t_push *push)
{
   cmd_rra(push, 0);
   cmd_rrb(push, 0);
   printf("rrr\n");
}