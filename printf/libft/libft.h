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

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd, int *i);
void	ft_putstr_fd(char *s, int fd, int *i);
void	ft_putnbr_fd(int n, int fd, int *i);

#endif
