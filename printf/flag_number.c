/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:50:45 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 17:40:19 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char	*flag_number(char *str, va_list args, int *i)
{
	while (*str == '#')
		str++;
	if (*str == 'o')
		return (ft_num_octal(str, va_arg(args, unsigned int), i));
	else if (*str == 'x')
		return (ft_num_sh(str, va_arg(args, unsigned int), i));
	else if (*str == 'X')
		return (ft_num_bh(str, va_arg(args, unsigned int), i));
	else if (*str == 'e')
		return (ft_num_e_small(str, va_arg(args, double), 0, i));
	else if (*str == 'E')
		return (ft_num_e_big(str, va_arg(args, double), 0, i));
	else if (*str == 'f')
		return (ft_num_f_small(str, va_arg(args, double), 0, i));
	else if (*str == 'F')
		return (ft_num_f_big(str, va_arg(args, double), 0, i));
	else if (*str == 'g')
		return (ft_num_g_small(str, va_arg(args, double), 0, i));
	else if (*str == 'G')
		return (ft_num_g_big(str, va_arg(args, double), 0, i));
	return (0);
}
