#include "so_long.h"

int main(int agrc, char **argv)
{
    t_map map;

    map = (t_map) {0};
    if (agrc != 2)
        return (ft_putstr_fd("Error\n./so_long mapname.ber\n", 2), 1);
    read_map(&map, argv[1]);
    visual (&map);
}
