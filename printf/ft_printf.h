/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:20:42 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:47:04 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_flag
{
    int plus;
    int min;
    int space;
    int dot;
    int sharp;
    int width;
    int zero;
} t_flag;

int	ft_printf(const char *str, ...);
void	ft_put_us_num(unsigned int nbr, int *i);
void	ft_put_small_hex(unsigned int nbr, int *i);
void	ft_put_addr_helper(unsigned long nbr, int *i);
void	ft_put_addr(void *add, int *i);
void	ft_put_big_hex(unsigned int nbr, int *i);
void	format_check(char *str, va_list args, int *i, t_flag *flag);
int	addr_len(unsigned long nbr);
int	hex_len(unsigned int nbr);
int	us_len(unsigned int nbr);
int	ft_numlen(int num);

#endif
