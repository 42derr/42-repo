#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIDE_LEN 800
#define NUM_SPIKES 5
#define HEDGE_SIZE 100

typedef struct s_img
{
    void    *img_ptr;
    char    *img_pixels_ptr;
    int     bits_per_pixel;
    int     endian;
    int     line_len;
}               t_img;

typedef struct s_var
{
    void    *mlx;
    void    *win;
    t_img   img;
    void    *hedge_img;
    void    *portal_img;
    void    *spike_img;
}               t_var;

void    my_pixel_put(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));    
    *((unsigned int *)(img->img_pixels_ptr + offset)) = color;
}

void    draw_image(t_var *data, void *img, int x, int y)
{
    mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void    draw_edges(t_var *data)
{
    int x, y;

    // Draw hedge image on the top edge
    for (x = 0; x < SIDE_LEN; x += HEDGE_SIZE)
        draw_image(data, data->hedge_img, x, 0);

    // Draw hedge image on the bottom edge
    for (x = 0; x < SIDE_LEN; x += HEDGE_SIZE)
        draw_image(data, data->hedge_img, x, SIDE_LEN - HEDGE_SIZE);

    // Draw hedge image on the left edge
    for (y = 0; y < SIDE_LEN; y += HEDGE_SIZE)
        draw_image(data, data->hedge_img, 0, y);

    // Draw hedge image on the right edge
    for (y = 0; y < SIDE_LEN; y += HEDGE_SIZE)
        draw_image(data, data->hedge_img, SIDE_LEN - HEDGE_SIZE, y);
}

void    draw_random_images(t_var *data)
{
    int x, y;

    // Draw hedge images on all edges
    draw_edges(data);

    // Draw a random portal image
    x = rand() % (SIDE_LEN - HEDGE_SIZE);
    y = rand() % (SIDE_LEN - HEDGE_SIZE);
    draw_image(data, data->portal_img, x, y);

    // Draw 5 random spikes
    for (int i = 0; i < NUM_SPIKES; i++)
    {
        x = rand() % (SIDE_LEN - HEDGE_SIZE);
        y = rand() % (SIDE_LEN - HEDGE_SIZE);
        draw_image(data, data->spike_img, x, y);
    }
}

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        exit(1);

    return 0;
}

int main()
{
    t_var   vars;

    srand(time(NULL)); // Seed for random number generation

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "XPM Texture");

    // Load the XPM files
    vars.hedge_img = mlx_xpm_file_to_image(vars.mlx, "xpm/hedge.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.portal_img = mlx_xpm_file_to_image(vars.mlx, "xpm/portal.xpm", &vars.img.line_len, &vars.img.line_len);
    vars.spike_img = mlx_xpm_file_to_image(vars.mlx, "xpm/spike.xpm", &vars.img.line_len, &vars.img.line_len);

    if (!vars.hedge_img || !vars.portal_img || !vars.spike_img)
    {
        fprintf(stderr, "Failed to load XPM files.\n");
        return 1;
    }

    // Retrieve image properties
    vars.img.img_ptr = vars.hedge_img;
    vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, 
                                                &vars.img.bits_per_pixel, 
                                                &vars.img.line_len, 
                                                &vars.img.endian);

    // Draw images
    draw_random_images(&vars);

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
