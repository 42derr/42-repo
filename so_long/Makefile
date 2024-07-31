CC = cc
CFLAGS = 

NAME = so_long
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = visual.c \
	  so_long.c \
	  swap.c \
      get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c \
      
OBJ = $(SRC:.c=.o)

# Targets
all: $(NAME)

# Link the final executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

# Build libft with bonus
$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

# Clean object files and library
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
