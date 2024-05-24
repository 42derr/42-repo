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

int		addr_len(long nbr);
int		flag_width_len(char *str, va_list args);
int		hex_len(unsigned int nbr);
int		us_len(unsigned int nbr);
int		octal_len(unsigned int nbr);
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
char	*ft_num_octal(char *str, unsigned int nbr, int *i);
char	*ft_num_sh(char *str, unsigned int nbr, int *i);
char	*ft_num_bh(char *str, unsigned int nbr, int *i);
void	ft_putoctal(unsigned int nbr, int *i);
int		maxval(int size);
void	ft_num_fp(double num, int n, int *i);
void	ft_num_fn(double num, int n, int *i);
char	*ft_num_f_small(char *ptr, double num, int n, int *i);
char	*ft_num_f_big(char *ptr, double num, int n, int *i);
char	*ft_num_g_small(char *ptr, double num, int n, int *i);
char	*ft_num_g_big(char *ptr, double num, int n, int *i);
void	ft_num_eplen(double num, int *i);
void	ft_num_enlen(double num, int *i);
void	ft_num_ep(double num, int n, int *i);
char	*ft_num_e_small(char *ptr, double num, int n, int *i);
char	*ft_num_e_big(char *ptr, double num, int n, int *i);
int		ft_printf(const char *str, ...);

#endif
