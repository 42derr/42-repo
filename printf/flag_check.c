/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:50 by dfasius           #+#    #+#             */
/*   Updated: 2024/06/06 19:05:31 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	flag_loop_helper(int *value, char **str, int *i)
{
	if (**str == '.')
	{
		(*i)++;
		(*str)++;
	}
	*value = ft_atoi(*str);
	while (**str >= '0' && **str <= '9')
	{
		(*i)++;
		(*str)++;
	}
}

int	flag_loop_check(char c)
{
	if (c == '-' || c == '+' || c == '#' || c == '0' || c == ' ')
		return (2);
	if (c == '.' || (c >= '1' && c <= '9'))
		return (1);
	return (0);
}

void	flag_loop(t_flag *flag, char **str, int *i)
{
	while (flag_loop_check(**str))
	{
		if (**str == '-')
			flag->min = 1;
		else if (**str == '+')
			flag->plus = 1;
		else if (**str == ' ')
			flag->space = 1;
		else if (**str == '#')
			flag->sharp = 1;
		else if (**str == '0')
			flag->zero = 1;
		else if (**str == '.')
		{
			flag->dot = 1;
			flag_loop_helper(&(flag->dotvalue), str, i);
		}
		else if (**str >= '1' && **str <= '9')
			flag_loop_helper(&(flag->width), str, i);
		if (flag_loop_check(**str) == 2)
		{
			(*i)++;
			(*str)++;
		}
	}
}

void	clear_flag(t_flag *flag)
{
	flag->plus = 0;
	flag->min = 0;
	flag->space = 0;
	flag->dot = 0;
	flag->sharp = 0;
	flag->width = 0;
	flag->zero = 0;
	flag->front = 0;
	flag->middle = 0;
	flag->dotvalue = 0;
	flag->back = 0;
	flag->str = 0;
	flag->neg = 0;
}

int	len_flag_check(t_flag *flag, char *str)
{
	if ((flag->min || flag->sharp || flag->zero || flag->plus || flag->space
			|| flag->width || flag->dot) && (*str == 'c'
			|| *str == 's' || *str == 'p' || *str == 'd'
			|| *str == 'i' || *str == 'u' || *str == 'x' || *str == 'X'))
		return (1);
	return (0);
}
