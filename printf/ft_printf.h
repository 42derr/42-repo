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

typedef struct s_flag
{
    int plus;
    int min;
    int space;
    int dot;
    int sharp;
    int width;
    int zero;
    int front;
    int middle;
    int dotvalue;
    int back;
    int str;
    int neg;
} t_flag;

int	ft_printf(const char *str, ...);

void	ft_put_us_num(unsigned int nbr, int *i, t_flag *flag);
void	ft_put_small_hex(unsigned int nbr, int *i, t_flag *flag);
void	ft_put_addr(void *add, int *i);
void	ft_put_big_hex(unsigned int nbr, int *i, t_flag *flag);
void	ft_put_addr_helper(unsigned long nbr, int *i);

int	addr_len(unsigned long nbr);
int	hex_len(unsigned int nbr, t_flag *flag);
int	us_len(unsigned int nbr, t_flag *flag);
int	ft_numlen(int num, t_flag *flag);

void	format_check(char *str, va_list args, int *i, t_flag *flag);

void    flag_loop(t_flag *flag, char **str);
void    flag_loop_helper(int *value, char **str);
int	format_length(char *str, va_list args, t_flag *flag);
void  len_flag(t_flag *flag, va_list args, char *str);
void  clear_flag (t_flag *flag);
void	ft_putnbr_helper(int n, int *i, t_flag *flag);


#endif
