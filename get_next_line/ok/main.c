#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

int null_check_gnl(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return 0;
    }

    char *line = get_next_line(fd);
    if (line != NULL)
    {
        free(line);
        fprintf(stderr, "Expected NULL but got a line for file: %s\n", filename);
        close(fd);
        return 0;
    }

    close(fd);
    return 1;
}

int main()
{
    const char *test_files[] = {
        "test_empty.txt",
        "test_no_newline.txt",
        "test_with_newline.txt",
        "non_existent_file.txt"
    };

    for (int i = 0; i < sizeof(test_files) / sizeof(test_files[0]); i++)
    {
        int result = null_check_gnl(test_files[i]);
        printf("null_check_gnl(%s) returned %s\n", test_files[i], result ? "1 (Pass)" : "0 (Fail)");
    }

    return 0;
}
