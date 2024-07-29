#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define SIDE_LEN 800

typedef struct s_img
{
    void    *img_ptr;
    char    *img_pixels_ptr;
    int     bits_per_pixel;
    int     endian;
    int     line_len;
    int     width;
    int     height;
}               t_img;

typedef struct s_var
{
    void    *mlx;
    void    *win;
    t_img   img;
    void    *xpm_img;
}               t_var;

void    my_pixel_put(t_img *img, int x, int y, int color)
{
    int offset;

    offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));    
    *((unsigned int *)(img->img_pixels_ptr + offset)) = color;
}

void    draw_xpm_tiling(t_var *data)
{
    int x, y;
    int img_width = data->img.width;
    int img_height = data->img.height;

    for (y = 0; y < SIDE_LEN; y += img_height)
    {
        for (x = 0; x < SIDE_LEN; x += img_width)
        {
            mlx_put_image_to_window(data->mlx, data->win, data->xpm_img, x, y);
        }
    }
}

int     f(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        exit(1);

    // Update the image with tiled XPM texture
    draw_xpm_tiling(data);

    return 0;
}

int main()
{
    t_var   vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "Tiled XPM Texture");

    // Load the XPM file and get its dimensions
    vars.xpm_img = mlx_xpm_file_to_image(vars.mlx, "hedge.xpm", &vars.img.width, &vars.img.height);
    if (!vars.xpm_img)
    {
        fprintf(stderr, "Failed to load XPM file.\n");
        return 1;
    }

    // Retrieve image properties
    vars.img.img_ptr = vars.xpm_img;
    vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, 
                                                &vars.img.bits_per_pixel, 
                                                &vars.img.line_len, 
                                                &vars.img.endian);

    printf("Image width: %d\nImage height: %d\n", vars.img.width, vars.img.height);
    printf("Line_len %d <-> SIDE_LEN %d\n"
           "bpp %d\n"
           "endian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

    mlx_key_hook(vars.win, f, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
