#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "so_long.h"

void    draw_image(t_var *data, void *img, int x, int y)
{
    mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void    draw_random_images(t_var *data, t_map *map)
{
    int x, y;
    int j;
    t_list *maplist = map->map_lst;

    y = 0;
    while (maplist)
    {
        j = 0;
        x = 0;
        while (j < map->width)
        {
            if (((char *)maplist->content)[j] == '1')
                draw_image(data, data->hedge_img, x, y);
            else if (((char *)maplist->content)[j] == '0')
                draw_image(data, data->wood_img, x, y);
            else if (((char *)maplist->content)[j] == 'P')
                draw_image(data, data->calf_img, x, y);
            else if (((char *)maplist->content)[j] == 'E')
                draw_image(data, data->portal_img, x, y);
            else if (((char *)maplist->content)[j] == 'C')
                draw_image(data, data->rose_img, x, y);
            j++;
            x += 32;
        }
        y += 32;
        maplist = maplist->next;
    }
}

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        exit(1);
    // if (keysym == XK_w)
    //     w_move(map->map_lst);
    // else if (keysym == XK_a)
    //     a_move(map->map_lst);
    // else if (keysym == XK_s)
    //     s_move(map->map_lst);
    // else if (keysym == XK_d)
    //     d_move(map->map_lst);


    printf("The %d key (ESC) has been pressed\n\n", keysym);
}

int visual(int width, int height, t_map *map)
{
    t_var   vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, width, height, "so_long");

    vars.hedge_img = mlx_xpm_file_to_image(vars.mlx, "xpm/hedge.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.portal_img = mlx_xpm_file_to_image(vars.mlx, "xpm/portal.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.spike_img = mlx_xpm_file_to_image(vars.mlx, "xpm/spike.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.wood_img = mlx_xpm_file_to_image(vars.mlx, "xpm/woodback.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.calf_img = mlx_xpm_file_to_image(vars.mlx, "xpm/calf.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.rose_img = mlx_xpm_file_to_image(vars.mlx, "xpm/rose.xpm", &vars.img.line_len, &vars.img.line_len);

    if (!vars.hedge_img || !vars.portal_img || !vars.spike_img || !vars.wood_img || !vars.calf_img || !vars.rose_img)
    {
        fprintf(stderr, "Failed to load XPM files.\n");
        return 1;
    }


    draw_random_images(&vars, map);
        printf("%s\n",(char *)(( map->map_lst)->content));

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
