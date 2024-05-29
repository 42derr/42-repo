#include "libft/libft.h"
#include "ft_printf.h"

char	*flag_space(char *str, va_list args, int *i)
{
	int	print;

	print = 0;
	while (*str == ' ')
		str++;
	if (*str >= '0' && *str <= '9')
		print = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	format_check_space(str, args, i, print);
	str++;
	return (str);
}
