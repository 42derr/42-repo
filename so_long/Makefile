CC = cc

CFLAGS_NORMAL = -Wall -Wextra -Werror -I./so_long_normal

CFLAGS_BONUS = -Wall -Wextra -Werror -I./so_long_bonus

NAME = so_long

NAME_BONUS = so_long_bonus

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =        get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c \

SRCS_NORMAL = so_long_normal/visual.c \
	  		  so_long_normal/visual_helper.c \
	  		  so_long_normal/visual_utils.c \
	  		  so_long_normal/so_long.c \
	  		  so_long_normal/error.c \
	          so_long_normal/display_move.c \
	          so_long_normal/parse_map.c \
	          so_long_normal/parse_map_help.c \
	          so_long_normal/validate_map.c \

SRCS_BONUS =  so_long_bonus/visual_bonus.c \
	  		  so_long_bonus/visual_helper_bonus.c \
	  		  so_long_bonus/visual_sprites_bonus.c \
	  		  so_long_bonus/visual_utils_bonus.c \
	  		  so_long_bonus/destroy_sprites_bonus.c \
	  		  so_long_bonus/so_long_bonus.c \
	  		  so_long_bonus/error_bonus.c \
	          so_long_bonus/display_move_bonus.c \
	          so_long_bonus/parse_map_bonus.c \
	          so_long_bonus/parse_map_help_bonus.c \
	          so_long_bonus/validate_map_bonus.c \
			  so_long_bonus/validate_map_utils_bonus.c \
	          so_long_bonus/load_sprites_bonus.c \

OBJS = $(SRCS:.c=.o) $(SRCS_NORMAL:.c=.o)

OBJS_BONUS = $(SRCS:.c=.o) $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(OBJS_BONUS) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)
	touch $(NAME_BONUS)

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
