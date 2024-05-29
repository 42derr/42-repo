
#include "libft/libft.h"
#include "ft_printf.h"

int	flag_min_len(char *str, va_list args)
{
	while (*str == '-' || (*str >= '0' && *str <= '9'))
		str++;
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (addr_len(va_arg(args, long)));
	else if (*str == 'd')
		return (ft_numlen(va_arg(args, int)));
	else if (*str == 'i')
		return (ft_numlen(va_arg(args, int)));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == '%')
		return (1);
	return (0);
}

char	*flag_min(char *str, va_list args, int *i)
{
	int		cur;
	int		print;
	va_list	args2;

	va_copy (args2, args);
	cur = flag_min_len(str, args2);
	print = 0;
	while (*str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
		format_check(str, args, i);
		return (str + 1);
	}
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '%')
	{
		ft_putchar_fd('%', 1, i);
		return (str + 1);
	}
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	if (*str == '.')
	{
		print = print - ft_atoi(str + 1);
		str = flag_dot(str, args, i);
	}
	else
	{
		format_check(str, args, i);
		str++;
	}
	while (print--)
		ft_putchar_fd (' ', 1, i);
	return (str);
}

/*
count 3 ->
the width
the stirng after manipulation
the presicion
*/