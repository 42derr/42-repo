#include "pushswap.h"

void    radix_base4(t_push *push)
{
    int i;
    int max;

    push->stacka = base4_array(push);
    push->stackb = (char **) malloc (sizeof(char *) * push->asize);
    i = 0;
    max = max_base4(push->asize - 1);
    while (i < max)
    {
        if (i == 0)
        {
            i_zero(push, &i);
            i_first(push , i);
            i = 1;
        }
        else
            i_normal(push, i);
        if (i == max - 2 && !(isthere(push, 15 - (max - 1), '2')) 
        && !(isthere(push, 15 - (max - 1), '3')))
            i_last_spes(push, i , max);
        i_return (push, i, max);
        i++;
    }
}   