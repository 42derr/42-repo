/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:11:46 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/21 19:16:33 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>


void    ft_puthex(long  nbr)
{
        char    c;

        if (nbr > 15)
        {
                ft_puthex(nbr / 16);
                ft_puthex(nbr % 16);
        }
        else
        {
                c = "0123456789abcdef"[nbr];
                write (1, &c, 1);
        }
}

int	main(void)
{
	char	p = 'a';
	long pointer = (long) &p;

	ft_puthex(pointer);
	printf("\n%p", &p);
	//write (1, &p, );
}
