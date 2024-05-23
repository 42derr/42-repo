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

#include "libft.h"
#include "libprint.h"

char	*flag_number(char *str, va_list args)
{
	while (*str == '#')
		str++;
	if (*str == 'o')
		return (ft_num_octal(str, va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (ft_num_sh(str, va_arg(args, unsigned int)));
	else if (*str == 'X')
		return (ft_num_bh(str, va_arg(args, unsigned int)));
	else if (*str == 'e')
		return (0);
	else if (*str == 'E')
		return (0);
	else if (*str == 'f')
		return (ft_num_f_small(str, va_arg(args, unsigned int), 0));
	else if (*str == 'F')
		return (ft_num_f_big(str, va_arg(args, unsigned int), 0));
	else if (*str == 'g')
		return (ft_num_g_small(str, va_arg(args, unsigned int), 0));
	else if (*str == 'G')
		return (ft_num_g_big(str, va_arg(args, unsigned int), 0));
	return (0);
}
