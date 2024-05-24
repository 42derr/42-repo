/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:31:52 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:18:13 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putchar_fd(char c, int fd, int *i)
{
	*i += write(fd, &c, 1);
}
/*
int	main(void)
{
	ft_putchar_fd('c',2);
}
*/
