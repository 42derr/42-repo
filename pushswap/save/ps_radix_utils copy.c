#include "pushswap.h"


char    *base4_string(int num)
{
    char    *str;
    int i;

    i = 19;

    str = (char *)malloc (sizeof(char) * 21);
    str[20] = '\0';
    while (num > 0 && i >= 0)
    {
        str[i] = (num % 3) + '0';
        num = num / 3;
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
        buffer[i] = base4_string(push->astart[i]);
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
        if ((push->stacka[i])[num] == c)
            j++;
        i++;
    }
    return (j);
}

int     howmanyb(t_push *push, int num, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < push->bsize)
    {
        if ((push->stackb[i])[num] == c)
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
        if ((push->stacka[i])[num] == c)
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
        if ((push->stackb[i])[num] == c)
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
        num = num / 3;
        i++;
    }
    return (i);
}

// int base4ToDecimal(char *base4) {
//     int length;
//     int decimal;
//     int pow;
//     int i;
//     int numericValue;

//     length = strlen(base4);
//     decimal = 0;
//     pow = 1;
//     i = length - 1;

//     while (i >= 0)
//     {
//         numericValue = base4[i] - '0';
//         decimal += numericValue * pow;
//         pow *= 4;
//         i--;
//     }

//     return decimal;
// }

// int    check_stack_f(t_push *push)
// {
//     int i;
//     int first;
//     int second;

//     if (push->bgroupsize != 0)
//         return (0);

//     i = 0;
//     while (i < push->agroupsize - 1)
//     {
//         first = base4ToDecimal(push->stacka[i]->buffer);
//         second = base4ToDecimal(push->stacka[i + 1]->buffer);
//         if (first < second)
//             return (0);
//         i++;
//     }
//     return (1);
// }