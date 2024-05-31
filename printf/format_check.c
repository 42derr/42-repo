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

char	*format_check(char *str, va_list args, int *i)
{
	if (*str == 'c')
		ft_putchar_fd (va_arg(args, int), 1, i);
	else if (*str == 's')
		ft_putstr_fd (va_arg(args, char *), 1, i);
	else if (*str == 'p')
		ft_putaddr (va_arg(args, void *), i);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1, i);
	else if (*str == 'u')
		ft_putusnbr (va_arg(args, unsigned int), i);
	else if (*str == 'x')
		ft_puthex (va_arg(args, unsigned int), i);
	else if (*str == 'X')
		ft_puthex_big (va_arg(args, unsigned int), i);
	else if (*str == '%')
		ft_putchar_fd('%', 1, i);
	return (0);
}