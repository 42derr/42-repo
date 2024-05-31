/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:38:09 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:19:40 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_flag flag;
	char	*ptr;
	int		i;

	i = 0;
	va_start (args, str);
	ptr = (char *) str;
	while (*ptr)
	{
		if (*ptr == '%')
			flag_loop (flag, &ptr);
		if (*ptr == '\0')
			return (i);
		format_check(ptr, args, &i, &flag);
		ft_putchar_fd(*ptr, 1, &i);
		ptr++;
	}
	va_end(args);
	return (i);
}