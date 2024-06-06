/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:49:43 by dfasius           #+#    #+#             */
/*   Updated: 2024/06/06 18:50:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

int	addr_len(unsigned long nbr)
{
	int	i;

	i = 2;
	if (!nbr)
		return (5);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

int	hex_len(unsigned int nbr, t_flag *flag)
{
	int	i;

	if (nbr == 0 && flag->dot && !flag->dotvalue)
		return (0);
	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

int	us_len(unsigned int nbr, t_flag *flag)
{
	int	i;

	i = 0;
	if (nbr == 0 && flag->dot && !flag->dotvalue)
		return (0);
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	ft_numlen(int num, t_flag *flag)
{
	int	i;

	i = 0;
	if (num == 0 && flag->dot && !flag->dotvalue)
		return (0);
	if (num == 0)
		return (1);
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		num = num * -1;
		i++;
		if (flag->dot)
			i--;
		flag->neg = 1;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int	format_length(char *str, va_list args, t_flag *flag)
{
	if (*str == 'c')
	{
		va_arg(args, int);
		return (1);
	}
	else if (*str == 's')
	{
		flag->str = 1;
		return (ft_strlen(va_arg(args, char *), flag));
	}
	else if (*str == 'p')
		return (addr_len(va_arg(args, long)));
	else if (*str == 'd' || *str == 'i')
		return (ft_numlen(va_arg(args, int), flag));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int), flag));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int), flag));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int), flag));
	else if (*str == '%')
		return (1);
	return (0);
}
