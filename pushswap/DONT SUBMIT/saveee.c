#include "pushswap.h"

int base4ToDecimal(char *base4) {
    int length;
    int decimal;
    int pow;
    int i;
    int numericValue;

    length = strlen(base4);
    decimal = 0;
    pow = 1;
    i = length - 1;

    while (i >= 0)
    {
        numericValue = base4[i] - '0';
        decimal += numericValue * pow;
        pow *= 4;
        i--;
    }

    return decimal;
}

int    check_stack_f(t_push *push)
{
    int i;
    int first;
    int second;

    if (push->bgroupsize != 0)
        return (0);

    i = 0;
    while (i < push->agroupsize - 1)
    {
        first = base4ToDecimal(push->stackaaa[i]->buffer);
        second = base4ToDecimal(push->stackaaa[i + 1]->buffer);
        if (first < second)
            return (0);
        i++;
    }
    return (1);
}

void    radix_base4(t_push *push)
{
    int i;
    int max;
    int o;
    int k;
    int spes;

    push->stackaaa = base4_array(push);
    push->stackbbb = (t_buffer **) malloc (sizeof(t_buffer *) * push->agroupsize);
    push->bgroupsize = 0;

    i = 0;
    max = max_base4(push->agroupsize - 1);
    while (i < max)
    {
        if (check_stack_f(push))
            return ;
        if (push->agroupsize > 0 && (isthere(push, 15 - i, '0') && (isthere(push, 15 - i, '1') 
        && !(isthere(push, 15 - i, '2')) && !(isthere(push, 15 - i, '3')))))
        {
            spes = 1;
            k = howmany(push, 15 - i, '1');
            o = 0;
            while (push->agroupsize > 0 && isthere(push, 15 - i, '0'))
            {
                if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '0')
                {
                    cmd_pb(push);
                }
                else
                {
                    o++;
                    cmd_ra(push, 1);
                }
            }
            if (push->agroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_ra(push, 1); 
            }
        }
        else
        {
            o = 0;
            k = howmany(push, 15 - i, '3') + howmany(push, 15 - i, '2');

            while (push->agroupsize > 0 && (isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1')))
            {
                if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '1')
                {
                    cmd_pb(push);
                }
                if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '0')
                {
                    cmd_pb(push);
                    if ((isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1')) && (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '3' || ((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '2') && (push->stackaaa[push->agroupsize - 1])->size == 1 && (push->stackbbb[push->bgroupsize - 1])->size == 1)
                    {
                        cmd_rr(push);
                        o++;
                    }
                    else
                    {
                        // if ((isthereb(push, 15 - i, '1')))
                        // {
                            cmd_rb(push, 1);
                        // }
                    }
                }
                if (push->agroupsize == 0 || !((isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1'))))
                    break ;
                if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '3' 
                || ((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '2')
                {
                    cmd_ra(push, 1);        
                    o++;
                }
            }

            if (push->agroupsize > 1 && o != 0 && i != 0)
            {
                k = k % o;
                while (k--)
                    cmd_ra(push, 1); 
            }
        }

        k = howmany(push, 15 - i, '3');
        o = 0;
        while (push->agroupsize > 0 && isthere(push, 15 - i, '2'))
        {
            if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - i] == '2')
            {
                cmd_pb(push);
            }
            else
            {
                o++;
                cmd_ra(push, 1);
            }
        }

        if (push->agroupsize > 1 && o != 0  && i != 0 && spes == 0)
        {
            k = k % o;
            while (k--)
                cmd_ra(push, 1); 
        }

        if (i == 0)
        {
            while ((isthere(push, 15 - i, '3')))
            {
                if (((push->stackaaa[push->agroupsize - 1])->buffer)[15 - (i + 1)] == '3')
                {
                    cmd_ra(push, 1);
                }
                else
                {
                    cmd_pb(push);
                }
                if (!(isthere(push, 15 - (i + 1), '2')) && !(isthere(push, 15 - (i + 1), '1')) && !(isthere(push, 15 - (i + 1), '0')) )
                {
                    break ;
                }
            }

            i++;
            k = howmanyb(push, 15 - i, '2') + howmanyb(push, 15 - i, '1') + howmanyb(push, 15 - i, '0');
            o = 0;
            while (push->bgroupsize > 0 && isthereb(push, 15 - i, '3'))
            {
                if (((push->stackbbb[push->bgroupsize - 1])->buffer)[15 - i] == '3')
                {
                    cmd_pa(push);
                }
                else
                {
                    o++;
                    cmd_rb(push, 1);
                }
            }
            if (push->bgroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }

            k = howmanyb(push, 15 - i, '1') + howmanyb(push, 15 - i, '0');
            o = 0;
            while (push->bgroupsize > 0 && isthereb(push, 15 - i, '2'))
            {
                if (((push->stackbbb[push->bgroupsize - 1])->buffer)[15 - i] == '2')
                {
                    cmd_pa(push);
                }
                else
                {
                    o++;
                    cmd_rb(push, 1);
                }
            }
            if (push->bgroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }

            k = howmanyb(push, 15 - i, '0');
            o = 0;
            while (push->bgroupsize > 0 && isthereb(push, 15 - i, '1'))
            {
                if (((push->stackbbb[push->bgroupsize - 1])->buffer)[15 - i] == '1')
                {
                    cmd_pa(push);
                }
                else
                {
                    o++;
                    cmd_rb(push, 1);
                }
            }
            if (push->bgroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }

            o = 0;
            while ((isthereb(push, 15 - i, '0')))
            {
                if (((push->stackbbb[push->bgroupsize - 1])->buffer)[15 - (i + 1)] == '1')
                {
                    cmd_rb(push, 1);
                    o++;
                }
                else
                {
                    cmd_pa(push);
                }
                if (!(isthereb(push, 15 - (i + 1), '2')) && !(isthereb(push, 15 - (i + 1), '3')) && !(isthereb(push, 15 - (i + 1), '0')) )
                {
                    break ;
                }
            }

            k = push->bgroupsize;
            if (push->bgroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }
        }

        if (i < max - 2 && i >= 2)
        {
            o = 0;
            while ((isthereb(push, 15 - i, '0')) || (isthereb(push, 15 - i, '1')) || (isthereb(push, 15 - i, '2')))
            {
                if ((isthereb(push, 15 - i, '1') || isthereb(push, 15 - i, '2')) || spes == 1)
                {
                    cmd_pa(push);
                }
                else
                {
                    if (((push->stackbbb[0])->buffer)[15 - (i + 1)] == '0')
                    {
                        o++;
                        cmd_rrb(push,1);
                    }
                    else
                    {
                        cmd_rrb(push,1);
                        cmd_pa(push);
                    }
                    if (!(isthereb(push, 15 - (i + 1), '1')) && !(isthereb(push, 15 - (i + 1), '2')) && !(isthereb(push, 15 - (i + 1), '3')))
                    {
                        break ;
                    }
                }
            }

            k = push->bgroupsize;
            if (push->bgroupsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rrb(push, 1); 
            }
        }
        else
        {
            while (push->bgroupsize != 0 && i != 0 && i != 1)
            {
                if ((isthereb(push, 15 - i, '1') || isthereb(push, 15 - i, '2')) || spes == 1)
                {
                    cmd_pa(push);
                }
                else if (push->bgroupsize > 1)
                {
                    cmd_rrb(push,1);
                    cmd_pa(push);
                }
                else
                {
                    cmd_pa(push);
                }
            }
        }


        while (push->bgroupsize != 0 && i == 0)
        {
                cmd_pa(push);
        }
        spes = 0;
        i++;
    }
                        //     int j;
                        // printf("\nstack a\n");
                        // j = push->agroupsize;
                        // while (j--)
                        // {
                        //     printf("%s\n", (push->stackaaa[j]->buffer));
                        // }
                        // printf("\nstack b\n");
                        // j = push->bgroupsize;
                        // while (j--)
                        // {
                        //     printf("%s\n", (push->stackbbb[j]->buffer));
                        // }
}

// ./push_swap 2 1 3 4 5 6 7 8 9 10