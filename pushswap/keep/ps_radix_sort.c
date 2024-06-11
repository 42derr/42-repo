#include "pushswap.h"

int     isthere_bytes(t_push *push, int num, int c)
{
    int i;

    i = 0;
    while (i < push->asize)
    {
        if ((push->stacka[i] >> num & 1) == c)
            return (1);
        i++;
    }
    return (0);
}

int     howmany_bytes(t_push *push, int num, int c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < push->asize)
    {
        if ((push->stacka[i] >> num & 1) == c)
            j++;
        i++;
    }
    return (j);
}

int     max_base2(int num)
{
    int i;

    i = 0;

    while (num > 0)
    {
        num = num / 2;
        i++;
    }
    return (i);
}

void    radix_sort(t_push *push)
{
    int i;
    int max;
    int k;
    int o;

    i = 0;
    max = max_base2(push->asize - 1);
    while (i < max)
    {
        k = howmany_bytes(push, i, 1);
        o = 0;
        while (push->asize > 0 && isthere_bytes(push, i, 0))
        {
            if ((push->stacka[push->asize - 1] >> i & 1) == 0)
            {
                cmd_pb(push);
            }
            if (push->asize == 0 || !(isthere_bytes(push, i, 0)))
                break ;
            if (isthere_bytes(push, i, 0) &&!(push->stacka[push->asize - 1] >> i & 1) == 0)
            {
                cmd_ra(push, 1);        
                o++;
            }
        }
        
        k = k % o;
        if (k < push->asize / 2)
            while (k--)
                cmd_ra(push, 1);        
  
        while (push->bsize != 0)
        {
            cmd_pa(push);
        }
        i++;
    }
}

// ./push_swap 2 1 3 4 5 6 7 8 9 10