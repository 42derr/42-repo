/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:38:09 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/21 17:39:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
// flag -, +,  , #, 0, . , number;
char	*format_check(char *str, va_list args)
{
	if (*str == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (*str == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (*str == 'p')
		return (0);
	else if (*str == 'd')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (*str == 'i')
		return (0);
	else if (*str == 'u')
		return (0);
	else if (*str == 'x')
		return (0);
	else if (*str == 'X')
		return (0);
	else if (*str == '%')
		write(1, "%", 1);
	return (0);
}

int	flag_min_len(char *str, va_list args)
{
	while (*str == '-' || *str >= '0' && *str <= '9')
		str++;
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (0);
	else if (*str == 'd')
		return (ft_strlen(ft_itoa(va_arg(args, int))));
	else if (*str == 'i')
		return (0);
	else if (*str == 'u')
		return (0);
	else if (*str == 'x')
		return (0);
	else if (*str == 'X')
		return (0);
	else if (*str == '%')
		write(1, "%", 1);
	return (0);
}

char	*flag_min(char *str, va_list args)
{
	int	cur;
	int	print;

	cur = flag_min_len(str, args);
	print = 0;
	while (*str == '-')
		str++;
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	str = format_check(str, args);
	str++;
	while (print--)
		ft_putchar_fd(' ',1);
	return (str);
}

//num only
char	*flag_zero(char *str)
{
	char	*newstr;
	int		nbr;
	int		i;

	str++;
	i = 0;
	while (*str == '0')
		str++;
	if (*str >= '1' && *str <= '9')
	{
		nbr = ft_atoi(str);
		newstr = (char *) malloc (sizeof(char) * (nbr + 1));
		if (!newstr)
			return (0);
		while (nbr--)
		{
			newstr[i] = '0';
			i++;
		}
		newstr[i] = '\0';
		return (newstr);
	}
	return (0);
}

char	*flag_plus(char *str, int c)
{
	while (*str == '+')
		str++;
	if (c >= 0)
		ft_putchar_fd ('+', 1);
	return (str);
}

char	*flag_space(char *str)
{
	while (*str == ' ')
		str++;
	ft_putchar_fd (' ', 1);
	return (str);
}

//only number
char	*flag_number(char *str)
{
	return (0);
}


char	*flag_check(char *str, va_list args)
{
	if (*str == '-')
		return (flag_min(str, args));
	else if (*str == '+')
		return (flag_plus(str, va_arg(args, int)));
	else if (*str == ' ')
		return (flag_space(str));
	else if (*str == '#')
		return (flag_number(str));
	else if (*str == '0')
		return (flag_zero(str));
	else if (*str >= '0' && *str <= '9')
		return (flag_number(str));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	char	*ptr;
	int		x;

	x = 0;

	va_start (args, str);
	ptr = ft_strdup(str);
	while (*ptr)
	{
		if (*ptr == '%')
			x = 1;
		while (x == 1)
		{
			ptr = flag_check (ptr + 1, args);
			if (format_check(ptr, args))
				ptr++;
			x = 0;
		}
		if (!*ptr)
			return (0);
		ft_putchar_fd(*ptr,1);
		ptr++;
	}
	va_end(args);
	return (0);
}

// count how many arraywe neeed make % per array and join them after we finished with the string
// lol just keep writing

int     main(void)
{
        ft_printf("%-10s", "school");
        //printf("%d\n",10);
}

