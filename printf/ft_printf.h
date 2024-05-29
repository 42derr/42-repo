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

int		addr_len(unsigned long nbr);
int		flag_width_len(char *str, va_list args);
int		hex_len(unsigned int nbr);
int		us_len(unsigned int nbr);
char	*format_check(char *str, va_list args, int *i);
int		flag_min_len(char *str, va_list args);
int		flag_zero_len(char *str, va_list args);
char	*flag_min(char *str, va_list args, int *i);
char	*flag_zero(char *str, va_list args, int *i);
char	*flag_plus(char *str, va_list args, int *i);
char	*flag_space(char *str, va_list args, int *i);
char	*flag_number(char *str, va_list args, int *i);
char	*flag_width(char *str, va_list args, int *i);
char	*flag_check(char *str, va_list args, int *i);
void	ft_putusnbr(unsigned int nbr, int *i);
void	ft_puthex(unsigned int nbr, int *i);
void	ft_puthex_addr(unsigned long nbr, int *i);
void	ft_putaddr(void *add, int *i);
void	ft_puthex_big(unsigned int nbr, int *i);
char	*ft_num_sh(char *str, unsigned int nbr, int *i);
char	*ft_num_bh(char *str, unsigned int nbr, int *i);
int		ft_printf(const char *str, ...);
int     ft_numlen(int num);
char	*format_check_zero(char *str, va_list args, int *i, int print);
void	ft_putnbr_zero(int n, int fd, int *i, int print);
char	*flag_dot(char *str, va_list args, int *i);
int	flag_dot_len(char *str, va_list args);
char	*format_check_dot(char *str, va_list args, int *i, int w);
void	ft_putstr_dot(char *s, int fd, int *x, int w);
int	ft_numlendot(int num);
char	*format_check_space(char *str, va_list args, int *i, int print);

#endif
