/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:55:41 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 17:23:34 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

char	*flag_check(char *str, va_list args, int *i)
{
	if (*str == '-')
		return (flag_min(str, args, i));
	else if (*str == '+')
		return (flag_plus(str, args, i));
	else if (*str == ' ')
	{
		if (str[1] == '\0')
			return (str);
		return (flag_space(str, args, i));
	}
	else if (*str == '#')
		return (flag_number(str, args, i));
	else if (*str == '0' || *str == '.')
		return (flag_zero(str, args, i));
	else if (*str >= '1' && *str <= '9')
		return (flag_width(str, args, i));
	else
	{
		format_check(str, args, i);
		str++;
	}
	return (str);
}
