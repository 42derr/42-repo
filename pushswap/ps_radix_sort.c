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

void    new_array(t_push *push, int num)
{
    int i;

    i = push->agroupsize;
    while (i--)
    {
        if (base4ToDecimal(push->stackaaa[i]->buffer) > num)
        {
            push->stackaaa[i]->buffer = base4_string((base4ToDecimal(push->stackaaa[i]->buffer) - 1));
        }
    }
    resize_array(push);
}

void    resize_array(t_push *push)
{
    int i;
    int j;
    int k;
    int first;
    int second;

    i = push->agroupsize - 1;
    j = i - 1;
    while (j--)
    {
        first = base4ToDecimal(push->stackaaa[i]->buffer);
        second = base4ToDecimal(push->stackaaa[i - 1]->buffer);
        if (first + 1 == second)
        {
            push->agroupsize = push->agroupsize - 1;
            push->stackaaa[i]->size =  push->stackaaa[i]->size + 1;
            push->stackaaa[i - 1] =  push->stackaaa[i];
            while (i < push->agroupsize)
            {
                push->stackaaa[i] =  push->stackaaa[i + 1];
                i++;
            }
            new_array(push,second);
            break;
        }
        k++;
        i--;
    }
}


// void    radix_base4(t_push *push)
// {

    // push->stackaaa = base4_array(push);
    // push->stackbbb = (t_buffer **) malloc (sizeof(t_buffer *));
    // push->bgroupsize = 0;


// }



void    radix_base4(t_push *push)
{
    int i;
    int max;
    int o;
    int k;
    // int j;
    int spes;

    push->stackaaa = base4_array(push);
    push->stackbbb = (t_buffer **) malloc (sizeof(t_buffer *) * push->agroupsize);
    push->bgroupsize = 0;

    i = 0;
    max = max_base4(push->agroupsize - 1);
        // j = push->agroupsize;
        // while (j--)
        // {
        //     printf("%s\n", (push->stackaaa[j])->buffer);
        //     printf("%d\n", (push->stackaaa[j])->size);
        // }    
        // printf("\n\n");
    while (i < max)
    {
        // resize_array(push);
        // j = push->agroupsize;
        // while (j--)
        // {
        //     printf("%s\n", (push->stackaaa[j])->buffer);
        //     printf("%d\n", (push->stackaaa[j])->size);
        // }
        max = max_base4(push->agroupsize - 1);
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
                        if ((isthereb(push, 15 - i, '1')))
                        {
                            cmd_rb(push, 1);
                        }
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
        // printf("\nstack b , %d\n", push->bgroupsize);
        // printf("%s\n", (push->stackbbb[2])->buffer);
        // printf("%d\n", (push->stackbbb[2])->size);
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

        if (push->agroupsize > 1 && o != 0  && i != 0)
        {
            k = k % o;
            while (k--)
                cmd_ra(push, 1); 
        }

        // printf("stack a\n");
        // j = push->agroupsize;
        // while (j--)
        // {
        //     printf("%s\n", (push->stackaaa[j])->buffer);
        //     printf("%d\n", (push->stackaaa[j])->size);
        // }
        // printf("stack b , %d\n", push->bgroupsize);
        // printf("%s\n", (push->stackbbb[3])->buffer);
        // printf("%d\n", (push->stackbbb[3])->size);

        // while (j--)
        // {
        // }

        while (push->bgroupsize != 0)
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
        spes = 0;
        i++;
    }
}

// ./push_swap 2 1 3 4 5 6 7 8 9 10