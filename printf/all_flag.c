/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:29:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/21 15:56:05 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

//num && string
char	*flag_min(const char *str)
{
	char	*newstr;
	int		nbr;
	int		i;

	str++;
	i = 0;
	while (*str == '-')
		str++;
	if (*str >= '0' && *str <= '9')
	{
		nbr = ft_atoi(str);
		newstr = (char *) malloc (sizeof(char) * (nbr + 1));
		if (!newstr)
			return (0);
		while (nbr--)
		{
			newstr[i] = ' ';
			i++;
		}
		newstr[i] = '\0';
		return (newstr);
	}
	return (0);
}

//num only
char	*flag_zero(const char *str)
{
	char	*newstr;
	int		nbr;
	int		i;

	str++;
	i = 0;
	while (*str == '0')
		str++;
	if (*str >= '1' && *str <= '9')
	{
		nbr = ft_atoi(str);
		newstr = (char *) malloc (sizeof(char) * (nbr + 1));
		if (!newstr)
			return (0);
		while (nbr--)
		{
			newstr[i] = '0';
			i++;
		}
		newstr[i] = '\0';
		return (newstr);
	}
	return (0);
}

// only number
char	*flag_plus(const char *str)
{
	char	*newstr;
	int 	i;

	i = 0;
	while (*str == '+')
		str++;
	newstr = (char *) malloc (sizeof(char) * 2);
	if (!newstr)
		return (0);
	newstr[0] = '+';
	newstr[1] = '\0';
	return (newstr);
}

//only number
char	*flag_space(const char *str)
{
	char	*newstr;
	int 	i;

	i = 0;
	while (*str == ' ')
		str++;
	newstr = (char *) malloc (sizeof(char) * 2);
	if (!newstr)
		return (0);
	newstr[0] = ' ';
	newstr[1] = '\0';
	return (newstr);
}

//only number
char	*flag_number(const char *str)
{
	return (0);
}
