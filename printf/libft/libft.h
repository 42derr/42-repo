/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:07:52 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 16:31:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
#include "../ft_printf.h"

size_t	ft_strlen(const char *s, t_flag *flag);
int		ft_atoi(const char *nptr);
void	ft_putchar(char c, int *i);
void	ft_putstr(char *s, int *i, t_flag *flag);
void	ft_putnbr(long n, int *i, t_flag *flag);

#endif