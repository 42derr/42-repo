#include "so_long.h"

int num_len(int num)
{
    int i;

    i = 0;
    if (num == 0)
        return (1);
    while (num > 0)
    {
        num = num / 10;
        i++;
    }
    return (i);
}

void count_movement(t_var *data)
{
    char *number;
    int last;
    int move;

    if (data->string_move)
        free(data->string_move);
    move = data->move;
    last = num_len(move);
    number = (char *)malloc(sizeof(char) * (last + 1));
    if (!number)
        close_window(data) ;
    number[last] = '\0';
    last--;
    while (last >= 0)
    {
        number[last] = (move % 10) + 48;
        move = move / 10;
        last--;
    }
    data->string_move = ft_strjoin("Movement = ", number);
    free(number);
    if (!data->string_move)
        close_window(data) ;
}

void display_move(t_var *data)
{
    int x;
    int j;

    x = 0;
    j = 0;
    while (j < (data->map)->width)
    {
        draw_image(data, data->textures[2], x, ((data->map)->height * 32));
        j++;
        x += 32;
    }
    count_movement(data);
    mlx_string_put(data->mlx, data->win, 16, ((data->map)->height) * 32 + 20, 16777215, data->string_move);
}