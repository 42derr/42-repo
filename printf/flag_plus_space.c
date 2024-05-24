/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_plus_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:54:53 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:15:08 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

char	*flag_plus(char *str, va_list args, int *i)
{
	va_list	args2;

	va_copy (args2, args);
	while (*str == '+')
		str++;
	if (va_arg(args, int) >= 0)
		ft_putchar_fd ('+', 1, i);
	format_check(str, args2, i);
	str++;
	return (str);
}

char	*flag_space(char *str, va_list args, int *i)
{
	while (*str == ' ')
		str++;
	ft_putchar_fd (' ', 1, i);
	format_check(str, args, i);
	str++;
	return (str);
}
