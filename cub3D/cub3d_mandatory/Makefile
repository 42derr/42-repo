CC = cc

CFLAGS_NORMAL = -Wall -Wextra -Werror

NAME = cub3D

LIBFT_DIR = libft
MLX_DIR = "../minilibx-linux"

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		cub3d.c \
		map_validation/extract_map.c \
		map_validation/extract_elements.c \
		map_validation/extract_content.c \
		map_validation/check_map.c \
		map_validation/check_map_utils.c \
		error_handling/handle_error.c \
		error_handling/handle_error_map.c \
		error_handling/handle_error_utils.c \
		error_handling/handle_error_data.c \
		window/window.c \
		window/window_utils.c \
		window/init_struct.c \
		player/player.c \
		movement/movement.c \
		movement/update_movement.c \
		raycast/raycast.c \
		raycast/raycast_3d.c \
		raycast/raycast_helper.c \
		raycast/textures.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

bonus: $(NAME)

# DELETE THIS BEFORE SUBMISSION
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS_NORMAL) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
