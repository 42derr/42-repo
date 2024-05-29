/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_zero_min.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:52:57 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:17:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	flag_zero_len(char *str, va_list args)
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
		return (ft_numlen(va_arg(args, int)));
	else if (*str == 'i')
		return (ft_numlen(va_arg(args, int)));
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

char	*flag_zero(char *str, va_list args, int *i)
{
	int		cur;
	int		print;
	va_list	args2;

	va_copy (args2, args);
	cur = flag_zero_len(str, args2);
	print = 0;
	while (*str == '0')
		str++;
	if (*str == '-')
		return (flag_min(str, args, i));
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	format_check_zero(str, args, i, print);
	str++;
	return (str);
}