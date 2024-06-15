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

t_buffer    **base4_array(t_push *push)
{
    t_buffer **buffer;
    t_buffer *number;
    int i;

    i = 0;
    buffer = (t_buffer **) malloc (sizeof(t_buffer *) * push->asize);
    if (!buffer)
        return (0);
    while (i < push->asize)
    {
        number = (t_buffer *) malloc (sizeof(t_buffer));
        number->buffer = base4_string(push->stacka[i]);
        number->size = 1;
        buffer[i] = number;
        i++;
    }
    push->agroupsize = i;
    buffer[i] = 0;
    return (buffer);
}

int     howmany(t_push *push, int num, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < push->agroupsize)
    {
        if ((push->stackaaa[i])->buffer[num] == c)
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
    while (i < push->bgroupsize)
    {
        if ((push->stackbbb[i])->buffer[num] == c)
            j++;
        i++;
    }
    return (j);
}

int     isthere(t_push *push, int num, char c)
{
    int i;

    i = 0;
    while (i < push->agroupsize)
    {
        if ((push->stackaaa[i])->buffer[num] == c)
            return (1);
        i++;
    }
    return (0);
}

int     isthereb(t_push *push, int num, char c)
{
    int i;

    i = 0;
    while (i < push->bgroupsize)
    {
        if ((push->stackbbb[i])->buffer[num] == c)
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