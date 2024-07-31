/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/29 18:43:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
# include "llist.h"

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_map {
    struct s_list *map_lst;
    int height;
    int width;
    int exit;
    int start;
    int collectible;
} t_map;

void    read_map(t_map *map, int fd);


#endif
