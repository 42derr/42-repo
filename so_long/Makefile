CC = cc
CFLAGS = 

NAME = so_long
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = so_long_normal/visual.c \
	  		  so_long_normal/visual_helper.c \
	  		  so_long_normal/so_long.c \
	  		  so_long_normal/error.c \
	          so_long_normal/display_move.c \
	          so_long_normal/parse_map.c \
	          so_long_normal/parse_map_help.c \
	          so_long_normal/validate_map.c \
              get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
