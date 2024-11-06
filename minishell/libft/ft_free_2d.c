/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:29:12 by dfasius           #+#    #+#             */
/*   Updated: 2024/11/06 12:30:01 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr) && (*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	if (arr)
		free(*arr);
}
