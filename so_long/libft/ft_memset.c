/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:39:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/21 17:15:11 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	int		i;

	str = s;
	i = 0;
	while (n--)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[21] = "12345678901234567890";
	char	realstr[21] = "12345678901234567890";

	printf ("\nBefore memset: %s", str);
	printf ("\nBefore Real memset: %s \n", realstr);

	printf ("\nFake :%s",(char *) ft_memset (str + 5, '.', 5));
	printf ("\nReal :%s\n",(char *) memset (realstr + 5, '.',5));

	printf("\nAfter memset: %s", str);
	printf("\nAfter Real memset: %s \n", realstr);
}
*/
