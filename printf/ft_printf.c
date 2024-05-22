/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:38:09 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 18:58:25 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "libprint.h"
#include "stdio.h"

int	ft_printf(const char *str, ...)
{
	va_list args;
	char	*ptr;
	char	*ptr2;

	va_start (args, str);
	ptr = (char *) str;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr2 = ptr;
			ptr = flag_check (ptr + 1, args);
			if (!ptr)
			{
				ptr = ptr2 + 1;
				format_check(ptr, args);
				ptr++;
			}
		}
		if (*ptr == '\0')
			return (0);
		ft_putchar_fd(*ptr, 1);
		ptr++;
	}
	va_end(args);
	return (0);
}

int     main(void)
{
	int i;

        //ft_printf("char : %c\nstring : %s\npointer : %p\ndecimal : %d\ninteger : %i\nunsigned int : %u\ns hexadecimal : %x\nb hexadecimal : %X\npercent sign : %%\n", 'a', "hello", &i, 123, 123, 2147483650, 31, 47);
	printf("%#.2o", 1);
}

