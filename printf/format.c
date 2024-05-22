/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:51:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:13:43 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "libprint.h"

char	*format_check(char *str, va_list args)
{
	if (*str == 'c')
		ft_putchar_fd (va_arg(args, int), 1);
	else if (*str == 's')
		ft_putstr_fd (va_arg(args, char *), 1);
	else if (*str == 'p')
		ft_putaddr (va_arg(args, void *));
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1);
	else if (*str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1);
	else if (*str == 'u')
		ft_putusnbr (va_arg(args, unsigned int));
	else if (*str == 'x')
		ft_puthex (va_arg(args, unsigned int));
	else if (*str == 'X')
		ft_puthex_big (va_arg(args, unsigned int));
	else if (*str == '%')
		write(1, "%", 1);
	return (0);
}
