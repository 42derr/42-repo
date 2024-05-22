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
#include "libft.h"
#include "libprint.h"

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

void	ft_putoctal(unsigned int nbr)
{
	char	c;

	if (nbr > 7)
	{
		ft_putoctal (nbr / 8);
		ft_putoctal (nbr % 8);
	}
	else
	{
		c = "012345678"[nbr];
		ft_putchar_fd (c, 1);
	}
}

char	*ft_num_bh(char	*str, unsigned int nbr)
{
	write (1, "0", 1);
	write (1, "X", 1);
	ft_puthex_big (nbr);
	str++;
	return (str);
}

char	*ft_num_sh(char	*str, unsigned int nbr)
{
	write (1, "0", 1);
	write (1, "x", 1);
	ft_puthex (nbr);
	str++;
	return (str);
}

char	*ft_num_octal(char *str, unsigned int nbr)
{
	write (1, "0", 1);
	ft_putoctal (nbr);
	str++;
	return (str);
}
