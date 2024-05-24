# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 15:52:39 by dfasius           #+#    #+#              #
#    Updated: 2024/05/24 19:06:44 by dfasius          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCS_DIR = ./libft .

SRCS = flag_check.c \
      flag_number.c \
      flag_num_e.c \
      flag_num_f.c \
      flag_num_g.c \
      flag_num_octal.c \
      flag_plus_space.c \
      flag_width.c \
      flag_zero_min.c \
      format.c \
      format_length.c \
      format_put.c \
      ft_printf.c \
	  ./libft/ft_atoi.c \
      ./libft/ft_itoa.c \
      ./libft/ft_putchar_fd.c \
      ./libft/ft_putnbr_fd.c \
      ./libft/ft_putstr_fd.c \
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

# bonus: all
# 	ar rcs $(NAME) $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
