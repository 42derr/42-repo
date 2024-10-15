NAME = philo_bonus

SRCS = philo_bonus.c \
       philo_function_bonus.c \
       philo_utils_bonus.c \
       philo_execute_bonus.c \
       ft_itoa.c \

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY = all clean fclean re