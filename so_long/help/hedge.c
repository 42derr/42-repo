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

int     f(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        exit(1);

    // Update the image with XPM texture
    mlx_put_image_to_window(data->mlx, data->win, data->xpm_img, 0, 0);

    return 0;
}

int main()
{
    t_var   vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "XPM Texture");

    // Load the XPM file
    vars.xpm_img = mlx_xpm_file_to_image(vars.mlx, "hedge.xpm", &vars.img.line_len, &vars.img.line_len);
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

    printf("Line_len %d <-> SIDE_LEN %d\n"
           "bpp %d\n"
           "endian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

    mlx_key_hook(vars.win, f, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
