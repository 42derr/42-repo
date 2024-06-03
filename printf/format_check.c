/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:51:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:41:54 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

void	format_check(char *str, va_list args, int *i, t_flag *flag)
{
	int back;
	int front;

	back = flag->back;
	front = flag->front;
	while (front-- && front >= 0 && !(*str == '%'))
		ft_putchar(' ', i);
	if (*str == 'c')
		ft_putchar (va_arg(args, int), i);
	else if (*str == 's')
		ft_putstr (va_arg(args, char *), i, flag);
	else if (*str == 'p')
		ft_put_addr (va_arg(args, void *), i);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_helper (va_arg(args, int), i, flag);
	else if (*str == 'u')
		ft_put_us_num (va_arg(args, unsigned int), i,flag);
	else if (*str == 'x')
		ft_put_small_hex (va_arg(args, unsigned int), i, flag);
	else if (*str == 'X')
		ft_put_big_hex (va_arg(args, unsigned int), i, flag);
	else if (*str == '%')
		ft_putchar('%', i);

	while (back-- && back >= 0 && !(*str == '%'))
	{
		ft_putchar(' ', i);
	}
}