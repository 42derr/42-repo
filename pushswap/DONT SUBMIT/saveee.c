#include "pushswap.h"



// void    new_array(t_push *push, int num)
// {
//     int i;

//     i = push->agroupsize;
//     while (i--)
//     {
//         if (base4ToDecimal(push->stackaaa[i]->buffer) > num)
//         {
//             push->stackaaa[i]->buffer = base4_string((base4ToDecimal(push->stackaaa[i]->buffer) - 1));
//         }
//     }
//     resize_array(push);
// }
int     is_there_num(t_push *push, int num)
{
    int i;
    int first;

    i = 0;
    while (i < push->agroupsize - 1)
    {
        first = base4ToDecimal(push->stackaaa[i]->buffer);
        if (first == num)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void    resize_array(t_push *push)
{
    int i;
    int j;
    int k;
    int first;
    int second;
    int amount;

    i = push->agroupsize - 1;
    j = i - 1;
    while (j--)
    {
        amount = 1;
        first = base4ToDecimal(push->stackaaa[i]->buffer);
        second = base4ToDecimal(push->stackaaa[i - 1]->buffer);
        while (is_there_num(push, first + amount))
        {
            amount++;
            if (first + amount > push->agroupsize - 1)
                break ;
            if (!is_there_num(push, first + amount))
                break;
        }
        if (first + amount == second)
        {
            push->agroupsize = push->agroupsize - 1;
            push->stackaaa[i]->size =  push->stackaaa[i]->size + 1;
            push->stackaaa[i - 1] =  push->stackaaa[i];
            while (i < push->agroupsize)
            {
                push->stackaaa[i] =  push->stackaaa[i + 1];
                i++;
            }
            resize_array(push);
            break;
        }
        k++;
        i--;
    }
    return ;
}

// int    check_stack_ff(t_push *push, int num)
// {
//     int i;
//     int first;
//     int second;

//     if (push->bgroupsize != 0)
//         return (0);

//     i = 0;
//     while (i < push->agroupsize - 1)
//     {
//         first = push->stackaaa[i]->buffer[num];
//         second = push->stackaaa[i + 1]->buffer[num];
//         if (first == second || second < first)
//             i++;
//         else
//             return (0);
//     }
//     return (1);
// }
