#include "so_long.h"

int main(int agrc, char **argv)
{
    t_map map;

    map = (t_map) {0};
    if (agrc != 2)
        return (ft_putstr_fd("./so_long mapname\n", 2), 1);
    if (read_map(&map, argv[1]))
        return (1);
    //check visual now map parse is ok
    visual (&map);
}
