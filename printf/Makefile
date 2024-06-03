# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 15:52:39 by dfasius           #+#    #+#              #
#    Updated: 2024/05/24 21:03:55 by dfasius          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCS_DIR = ./libft .

SRCS = flag_check.c \
      format_check.c \
      format_length.c \
      format_print.c \
      ft_printf.c \
	  ./libft/ft_atoi.c \
      ./libft/ft_putchar.c \
      ./libft/ft_putnbr.c \
      ./libft/ft_putstr.c \
      ./libft/ft_strlen.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE

all: ${NAME}

.c.o:
	$(CC) $(CFLAGS) $(addprefix -I, $(INCS_DIR)) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

bonus: all
	ar rcs $(NAME) $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
