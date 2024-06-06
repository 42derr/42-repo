/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:13 by dfasius           #+#    #+#             */
/*   Updated: 2024/06/06 17:52:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ft_printf.h"
#include "libft.h"

void	ft_putstr(char *s, int *x, t_flag *flag)
{
	int	i;

	i = 0;
	if (flag && flag->dot && flag->dotvalue < 6 && !s)
		return ;
	if (s == NULL)
	{
		ft_putstr ("(null)", x, flag);
		return ;
	}
	while (s[i])
	{
		if (flag && flag->dot && flag->middle < i + 1)
			return ;
		ft_putchar(s[i], x);
		i++;
	}
}
