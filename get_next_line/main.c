// #include "get_next_line.h"
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>

// int main(void)
// {
//     char    *str;
//     int fd = open ("example.txt", O_RDONLY);
//     if (fd == -1)
//         return (0);

//     while ((str = get_next_line(fd))!= NULL)
//         printf("%s", str);

//     close(fd);
// }