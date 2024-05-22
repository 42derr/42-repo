/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_num_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:59 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_num_f(char *ptr, double num, int n)
{
	char	*str;
	int	idx;
	int	i;

	idx = 6;
	i = 0;
	if (num > 0)
	{
		while ((long) num < 21474836)
		{
			num = num * 10;
		}
		str = ft_itoa((int)num);
		ft_putchar_fd (str[0], 1);
		ft_putchar_fd ('.', 1);
		while (idx--)
		{
			ft_putchar_fd (str[i + 1], 1);
			i++;
		}
	}
	return (0);
}

int	main(void)
{
	printf("%#f",922337203685477570000000000000000000000.0);
	//ft_num_f ("hello", 1.7, 2);
}
