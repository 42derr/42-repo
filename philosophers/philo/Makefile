NAME = philo

SRCS = philo.c \
       philo_function.c \
       philo_utils.c \
       philo_execute.c \

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = 
# CFLAGS = -Wall -Werror -Wextra

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

.PHONY : all clean fclean re
