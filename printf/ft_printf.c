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

void	error_str(char *s, int *x)
{
	int	i;

	i = 0;

	while (s[i] == '%' || s[i] == '-' || s[i] == '+' || s[i] == '#'|| s[i] == ' ' 
    || s[i] == '0' || s[i] == '.' || (s[i] >= '1' && s[i] <= '9'))
	{
		ft_putchar(s[i], x);
		i++;
	}
}

void format_loop(char **ptr, va_list args, va_list args2, int *i)
{
	t_flag flag = {0};
	int x;

	x = 1;
	while (**ptr == '%')
	{
		(*ptr)++;
		flag_loop (&flag, ptr, &x);
		len_flag (&flag, args, *ptr);
		if (!(**ptr == 'c' || **ptr == 's' || **ptr == 'p' || **ptr == 'd' ||
		 **ptr == 'i' || **ptr == 'u' || **ptr == 'x' || **ptr == 'X' || **ptr == '%'))
		{
			error_str(*ptr - x, i);
			ft_putchar(**ptr, i);
			clear_flag (&flag);
			(*ptr)++;
			break ;
		}
		format_check(*ptr, args2, i, &flag);
		clear_flag (&flag);
		(*ptr)++;
	}	
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	va_list args2;
	char	*ptr;
	int		i;

	i = 0;
	va_start (args, str);
	va_copy(args2, args);
	ptr = (char *) str;
	while (*ptr)
	{
		format_loop(&ptr, args, args2, &i);
		if (*ptr == '\0')
			return (i);
		ft_putchar(*ptr, &i);
		ptr++;
	}
	va_end(args);
	return (i);
}