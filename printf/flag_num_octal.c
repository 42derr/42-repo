/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:55:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 17:40:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

int	octal_len(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr > 0)
	{
		nbr = nbr / 8;
		i++;
	}
	return (i);
}

void	ft_putoctal(unsigned int nbr, int *i)
{
	char	c;

	if (nbr > 7)
	{
		ft_putoctal (nbr / 8, i);
		ft_putoctal (nbr % 8, i);
	}
	else
	{
		c = "012345678"[nbr];
		ft_putchar_fd (c, 1, i);
	}
}

char	*ft_num_bh(char	*str, unsigned int nbr, int *i)
{
	if (nbr == 0)
	{
		ft_putchar_fd('0', 1, i);
		return (str + 1);
	}
	ft_putchar_fd('0', 1, i);
	ft_putchar_fd('X', 1, i);
	ft_puthex_big (nbr, i);
	str++;
	return (str);
}

char	*ft_num_sh(char	*str, unsigned int nbr, int *i)
{
	if (nbr == 0)
	{
		ft_putchar_fd('0', 1, i);
		return (str + 1);
	}
	ft_putchar_fd('0', 1, i);
	ft_putchar_fd('x', 1, i);
	ft_puthex (nbr, i);
	str++;
	return (str);
}

char	*ft_num_octal(char *str, unsigned int nbr, int *i)
{
	ft_putchar_fd('0', 1, i);
	ft_putoctal (nbr, i);
	str++;
	return (str);
}
