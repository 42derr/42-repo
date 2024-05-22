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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "libprint.h"
#include <unistd.h>

char	*flag_check(char *str, va_list args)
{
	if (*str == '-')
		return (flag_min(str, args));
	else if (*str == '+')
		return (flag_plus(str, args));
	else if (*str == ' ')
		return (flag_space(str, args));
	else if (*str == '#')
		return (flag_number(str, args));
	else if (*str == '0')
		return (flag_zero(str, args));
	else if (*str >= '1' && *str <= '9')
		return (flag_width(str, args));
	return (0);
}
