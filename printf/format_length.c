/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenght.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:49:43 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:14:10 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

int	addr_len(unsigned long nbr)
{
	int	i;

	i = 2;
	while (nbr > 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

int	hex_len(unsigned int nbr)
{
	int	i;

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

int	us_len(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	ft_numlen(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);	
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		num = num * -1;
		i++;
	}
	while (num > 0)
	{
		num = num / 10;
		i++; 
	}
	return (i);
}

int	ft_numlendot(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);	
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		num = num * -1;
	}
	while (num > 0)
	{
		num = num / 10;
		i++; 
	}
	return (i);
}