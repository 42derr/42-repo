/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprint.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:07:52 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 17:26:22 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPRINT_H
# define LIBPRINT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define NAN_VAL (0.0 / 0.0)
# define POS_INF (1.0 / 0.0)
# define NEG_INF (-1.0 / 0.0)

int		addr_len(long nbr);
int		flag_width_len(char *str, va_list args);
int		hex_len(unsigned int nbr);
int		us_len(unsigned int nbr);
int		octal_len(unsigned int nbr);
char	*format_check(char *str, va_list args);
int		flag_min_len(char *str, va_list args);
int		flag_zero_len(char *str, va_list args);
char	*flag_min(char *str, va_list args);
char	*flag_zero(char *str, va_list args);
char	*flag_plus(char *str, va_list args);
char	*flag_space(char *str, va_list args);
char	*flag_number(char *str, va_list args);
char	*flag_width(char *str, va_list args);
char	*flag_check(char *str, va_list args);
void	ft_putusnbr(unsigned int nbr);
void	ft_puthex(unsigned int nbr);
void	ft_puthex_addr(long nbr);
void	ft_putaddr(void *add);
void	ft_puthex_big(unsigned int nbr);
char	*ft_num_octal(char *str, unsigned int nbr);
char	*ft_num_sh(char *str, unsigned int nbr);
char	*ft_num_bh(char *str, unsigned int nbr);
void	ft_putoctal(unsigned int nbr);
int	    maxval(int size);
void	ft_num_fp(double num, int n);
void	ft_num_fn(double num, int n);
char	*ft_num_f_small(char *ptr, double num, int n);
char	*ft_num_f_big(char *ptr, double num, int n);


#endif
