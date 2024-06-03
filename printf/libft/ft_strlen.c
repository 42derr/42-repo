/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:21:19 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:05:54 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_strlen(const char *s, t_flag *flag)
{
	int	i;

	if (!s && flag->dot && flag->dotvalue < 6)
		return (0);
	if (!s)
		return (6);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}