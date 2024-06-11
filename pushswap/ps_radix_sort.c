#include "pushswap.h"

char    *base4_string(int num)
{
    char    *str;
    int i;

    i = 15;

    str = (char *)malloc (sizeof(char) * 17);
    str[16] = '\0';
    while (num > 0 && i >= 0)
    {
        str[i] = (num % 4) + '0';
        num = num / 4;
        i--;
    }
    while (i >= 0)
    {
        str[i] = '0';
        i--;
    }
    return (str);
}

char    **base4_array(t_push *push)
{
    char **buffer;
    int i;

    i = 0;
    buffer = (char **) malloc (sizeof(char *) * push->asize);
    if (!buffer)
        return (0);
    while (i < push->asize)
    {
        buffer[i] = base4_string(push->stacka[i]);
        i++;
    }
    buffer[i] = 0;
    return (buffer);
}

int     howmany(t_push *push, int num, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < push->asize)
    {
        if (push->stackaa[i][num] == c)
            j++;
        i++;
    }
    return (j);
}

int     isthere(t_push *push, int num, char c)
{
    int i;

    i = 0;
    while (i < push->asize)
    {
        if (push->stackaa[i][num] == c)
            return (1);
        i++;
    }
    return (0);
}

int     isthereb(t_push *push, int num, char c)
{
    int i;

    i = 0;
    while (i < push->bsize)
    {
        if (push->stackbb[i][num] == c)
            return (1);
        i++;
    }
    return (0);
}

int     max_base4(int num)
{
    int i;

    i = 0;

    while (num > 0)
    {
        num = num / 4;
        i++;
    }
    return (i);
}

void    radix_base4(t_push *push)
{
    int i;
    int max;
    int o;
    int k;

    push->stackaa = base4_array(push);
    push->stackbb = (char **) malloc (sizeof(char *) * push->asize);

    i = 0;
    max = max_base4(push->asize - 1);
    while (i < max)
    {
        o = 0;
        k = howmany(push, 15 - i, '3') + howmany(push, 15 - i, '2');

        while (push->asize > 0 && (isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1')))
        {
            if (push->stackaa[push->asize - 1][15 - i] == '1')
            {
                cmd_pb(push);
            }
            if (push->stackaa[push->asize - 1][15 - i] == '0')
            {
                cmd_pb(push);
                if ((isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1')) && (push->stackaa[push->asize - 1][15 - i] == '3' || push->stackaa[push->asize - 1][15 - i] == '2'))
                {
                    cmd_rr(push);
                    o++;
                }
                else
                {
                    cmd_rb(push, 1);
                }
            }
            if (push->asize == 0 || !((isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1'))))
                break ;
            if (push->stackaa[push->asize - 1][15 - i] == '3' || push->stackaa[push->asize - 1][15 - i] == '2')
            {
                cmd_ra(push, 1);        
                o++;
            }
        }

        if (push->asize > 1 && o != 0)
        {
            k = k % o;
            while (k--)
                cmd_ra(push, 1); 
        }

        k = howmany(push, 15 - i, '3');
        o = 0;
        while (push->asize > 0 && isthere(push, 15 - i, '2'))
        {
            if (push->stackaa[push->asize - 1][15 - i] == '2')
            {
                cmd_pb(push);
            }
            else
            {
                o++;
                cmd_ra(push, 1);
            }
        }

        if (push->asize > 1 && o != 0)
        {
            k = k % o;
            while (k--)
                cmd_ra(push, 1); 
        }


        while (push->bsize != 0)
        {
            if ((isthereb(push, 15 - i, '1') || isthereb(push, 15 - i, '2')))
            {
                cmd_pa(push);
            }
            else
            {
                cmd_rrb(push,1);
                cmd_pa(push);
            }
        }
        i++;
    }
}

// ./push_swap 2 1 3 4 5 6 7 8 9 10