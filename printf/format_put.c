/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:48:30 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:07:33 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

void	ft_putusnbr(unsigned int nbr, int *i)
{
	if (nbr > 9)
	{
		ft_putusnbr (nbr / 10, i);
		ft_putusnbr (nbr % 10, i);
	}
	else
	{
		ft_putchar_fd (nbr + '0', 1, i);
	}
}

void	ft_puthex(unsigned int nbr, int *i)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex (nbr / 16, i);
		ft_puthex (nbr % 16, i);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd (c, 1, i);
	}
}

void	ft_puthex_addr(unsigned long nbr, int *i)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_addr (nbr / 16, i);
		ft_puthex_addr (nbr % 16, i);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd (c, 1, i);
	}
}

void	ft_putaddr(void *add, int *i)
{
	unsigned long	nbr;

	if (!add)
	{
		ft_putstr_fd ("(nil)", 1, i);
		return ;
	}
	nbr = (unsigned long) add;
	ft_putchar_fd ('0', 1, i);
	ft_putchar_fd ('x', 1, i);
	ft_puthex_addr (nbr, i);
}

void	ft_puthex_big(unsigned int nbr, int *i)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_big (nbr / 16, i);
		ft_puthex_big (nbr % 16, i);
	}
	else
	{
		c = "0123456789ABCDEF"[nbr];
		ft_putchar_fd (c, 1, i);
	}
}
