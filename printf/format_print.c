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

void	ft_put_us_num(unsigned int nbr, int *i, t_flag *flag)
{
	if (nbr == 0 && flag->dot && !flag->dotvalue)
		return ;
	else
		flag->dot = 0;
	while (flag->middle > 0 && flag->zero == 1)
	{
		ft_putchar ('0', i);
		flag->middle--;
	}
	if (nbr > 9)
	{
		ft_put_us_num (nbr / 10, i, flag);
		ft_put_us_num (nbr % 10, i, flag);
	}
	else
	{
		ft_putchar (nbr + '0', i);
	}
}

void	ft_put_small_hex(unsigned int nbr, int *i, t_flag *flag)
{
	char	c;

	if (nbr == 0 && flag->dot && !flag->dotvalue)
		return ;	
	while (flag->middle > 0 && flag->zero == 1)
	{
		ft_putchar ('0', i);
		flag->middle--;
	}
	if (flag->sharp == 1 && nbr > 0)
	{
		ft_putstr ("0x", i, 0);
		flag->sharp = 0;
	}
	if (nbr > 15)
	{
		ft_put_small_hex (nbr / 16, i, flag);
		ft_put_small_hex (nbr % 16, i, flag);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar (c, i);
	}
}

void	ft_put_addr_helper(unsigned long nbr, int *i)
{
	char	c;

	if (nbr > 15)
	{
		ft_put_addr_helper (nbr / 16, i);
		ft_put_addr_helper (nbr % 16, i);
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar (c, i);
	}
}

void	ft_put_addr(void *add, int *i)
{
	unsigned long	nbr;

	if (!add)
	{
		ft_putstr ("(nil)", i, 0);
		return ;
	}
	nbr = (unsigned long) add;
	ft_putchar ('0', i);
	ft_putchar ('x', i);
	ft_put_addr_helper (nbr, i);
}

void	ft_put_big_hex(unsigned int nbr, int *i, t_flag *flag)
{
	char	c;

	if (nbr == 0 && flag->dot && !flag->dotvalue)
		return ;	
	while (flag->middle > 0 && flag->zero == 1)
	{
		ft_putchar ('0', i);
		flag->middle--;
	}
	if (flag->sharp == 1 && nbr > 0)
	{
		ft_putstr ("0X", i, 0);
		flag->sharp = 0;
	}
	if (nbr > 15)
	{
		ft_put_big_hex (nbr / 16, i, flag);
		ft_put_big_hex (nbr % 16, i, flag);
	}
	else
	{
		c = "0123456789ABCDEF"[nbr];
		ft_putchar (c, i);
	}
}
