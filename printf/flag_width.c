/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:45:23 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:50:08 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

int	flag_width_len(char *str, va_list args)
{
	while (*str == '.' || (*str >= '0' && *str <= '9'))
		str++;
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (addr_len(va_arg(args, long)));
	else if (*str == 'd')
		return (ft_strlen(ft_itoa(va_arg(args, int))));
	else if (*str == 'i')
		return (ft_strlen(ft_itoa(va_arg(args, int))));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == '%')
		return (1);
	return (0);
}

char	*flag_width(char *str, va_list args, int *i)
{
	int		cur;
	int		print;
	int		print2;
	va_list	args2;

	va_copy (args2, args);
	print2 = 0;
	cur = flag_width_len(str, args);
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '%')
	{
		ft_putchar_fd('%', 1, i);
		return (str + 1);
	}
	if (*str == '.')
	{
		print2 = ft_atoi (str + 1);
		if (print2 < cur)
			cur = print2;
	}
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	while (print--)
		ft_putchar_fd(' ', 1, i);
		
	if (*str == '.')
		return (flag_check(str, args2, i));
	format_check(str, args2, i);
	str++;
	return (str);
}
