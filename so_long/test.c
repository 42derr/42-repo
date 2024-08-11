#include "so_long.h"
#include <unistd.h> // For usleep()
#include <stdio.h>  // For printf() debugging
#define WIDTH 800
#define HEIGHT 600
#define SPRITE_SIZE 32
#define ANIMATION_DELAY 100000 // Delay in microseconds (0.1 seconds)

typedef enum {
    RIGHT,
    LEFT,
    FRONT,
    BACK
} t_direction;

typedef struct {
    void *mlx;
    void *win;
    void *sprites[4][4]; // 4 directions, 4 sprites each
    int current_sprite;
    int x;
    int y;
    int is_moving;
    t_direction direction;
} t_game;

void render(t_game *game) {
    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->sprites[game->direction][game->current_sprite], game->x, game->y);
}

int update(t_game *game) {
    if (game->is_moving) {
        game->current_sprite = (game->current_sprite + 1) % 4;
        if (game->direction == RIGHT) {
            game->x += SPRITE_SIZE / 4; // Move gradually to match the animation
        } else if (game->direction == LEFT) {
            game->x -= SPRITE_SIZE / 4; // Move gradually to match the animation
        } else if (game->direction == FRONT) {
            game->y -= SPRITE_SIZE / 4; // Move gradually to match the animation
        } else if (game->direction == BACK) {
            game->y += SPRITE_SIZE / 4; // Move gradually to match the animation
        }
        render(game);
        usleep(ANIMATION_DELAY); // Delay for smooth animation
        if (game->current_sprite == 0) {
            game->is_moving = 0; // Stop moving after one full cycle
        }
    }
    return 0;
}

int handle_keypress(int keycode, t_game *game) {
    if (keycode == XK_d && !game->is_moving) { // 'd' key for right
        game->direction = RIGHT;
        game->is_moving = 1;
    } else if (keycode == XK_a && !game->is_moving) { // 'a' key for left
        game->direction = LEFT;
        game->is_moving = 1;
    } else if (keycode == XK_w && !game->is_moving) { // 'w' key for front
        game->direction = FRONT;
        game->is_moving = 1;
    } else if (keycode == XK_s && !game->is_moving) { // 's' key for back
        game->direction = BACK;
        game->is_moving = 1;
    } else if (keycode == XK_Escape) { // 'Esc' key
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return 0;
}

int main() {
    t_game game;
    int img_width = SPRITE_SIZE;
    int img_height = SPRITE_SIZE;
    char *dirs[4] = {"right", "left", "front", "back"};

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Sprite Animation");

    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < 4; i++) {
            char filename[100];
            sprintf(filename, "textures/char/%s/%s%d.xpm", dirs[dir], dirs[dir], i + 1);
            game.sprites[dir][i] = mlx_xpm_file_to_image(game.mlx, filename, &img_width, &img_height);
            if (game.sprites[dir][i] == NULL) {
                printf("Error loading image: %s\n", filename);
            }
        }
    }

    game.current_sprite = 0;
    game.x = WIDTH / 2;
    game.y = HEIGHT / 2;
    game.is_moving = 0;
    game.direction = RIGHT; // Default direction

    render(&game);
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);  // Listen for keypress events
    mlx_loop_hook(game.mlx, update, &game);  // Continuously update the game state
    mlx_loop(game.mlx);

    return 0;
}
