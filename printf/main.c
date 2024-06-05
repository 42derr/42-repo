#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    printf("%d\n" , ft_printf("% k %s % k", "hello"));
    printf("%d\n" , printf("% k %s % k", "hello"));
    int i;
}

// to fix -> len flag

// printf