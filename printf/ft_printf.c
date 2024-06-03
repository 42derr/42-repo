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

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_flag flag = {0};
	va_list args2;
	char	*ptr;
	int		i;

	i = 0;
	va_start (args, str);
	va_copy(args2, args);
	ptr = (char *) str;
	while (*ptr)
	{
		while (*ptr == '%')
		{
			ptr++;
			flag_loop (&flag, &ptr);
			len_flag (&flag, args, ptr);
			format_check(ptr, args2, &i, &flag);
			clear_flag (&flag);
			if (*ptr == 'c' || *ptr == 's' || *ptr == 'p' || *ptr == 'd' ||
			 *ptr == 'i' || *ptr == 'u' || *ptr == 'x' || *ptr == 'X' || *ptr == '%')
				ptr++;
		}
		if (*ptr == '\0')
			return (i);
		ft_putchar(*ptr, &i);
		ptr++;
	}
	va_end(args);
	return (i);
}