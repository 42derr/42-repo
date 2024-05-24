/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:13 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:18:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd, int *x)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_fd ("(null)", 1, x);
		return ;
	}
	while (s[i])
	{
		*x = *x + 1;
		i++;
	}
	write (fd, s, i);
}
/*
int	main(void)
{
	ft_putstr_fd("hello", 1);
}
*/
