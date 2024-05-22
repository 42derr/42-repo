/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprint.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:07:52 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:22:21 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPRINT_H
# define LIBPRINT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		addr_len(long nbr);
int		hex_len(unsigned int nbr);
int		us_len(unsigned int nbr);
char	*format_check(char *str, va_list args);
int		flag_min_len(char *str, va_list args);
int		flag_zero_len(char *str, va_list args);
char	*flag_min(char *str, va_list args);
char	*flag_zero(char *str, va_list args);
char	*flag_plus(char *str, va_list args);
char	*flag_space(char *str, va_list args);
char	*flag_number(char *str);
char	*flag_width(char *str);
char	*flag_check(char *str, va_list args);
void	ft_putusnbr(unsigned int nbr);
void	ft_puthex(unsigned int nbr);
void	ft_puthex_addr(long nbr);
void	ft_putaddr(void *add);
void	ft_puthex_big(unsigned int nbr);

#endif
