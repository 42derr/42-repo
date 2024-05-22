/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:48:30 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:10:01 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "libprint.h"

void	ft_putusnbr(unsigned int nbr)
{
	if (nbr > 9)
	{
		ft_putusnbr (nbr / 10);
		ft_putusnbr (nbr % 10);
	}
	else
	{
		ft_putchar_fd (nbr + '0', 1);
	}
}

void	ft_puthex(unsigned int nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex (nbr / 16);
		ft_puthex (nbr % 16);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd (c, 1);
	}
}

void	ft_puthex_addr(long nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_addr (nbr / 16);
		ft_puthex_addr (nbr % 16);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd (c, 1);
	}
}

void	ft_putaddr(void *add)
{
	long	nbr;

	nbr = (long) add;
	write (1, "0", 1);
	write (1, "x", 1);
	ft_puthex_addr (nbr);
}

void	ft_puthex_big(unsigned int nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_big (nbr / 16);
		ft_puthex_big (nbr % 16);
	}
	else
	{
		c = "0123456789ABCDEF"[nbr];
		ft_putchar_fd (c, 1);
	}
}
