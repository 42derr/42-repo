
#include "libft/libft.h"
#include "ft_printf.h"


int	flag_dot_len(char *str, va_list args)
{
	while (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == 'd')
		return (ft_numlendot(va_arg(args, int)));
	else if (*str == 'i')
		return (ft_numlendot(va_arg(args, int)));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int)));
	return (0);
}

char	*flag_dot(char *str, va_list args, int *i)
{
	int		cur;
	int		print;
	int		print2;
	va_list	args2;

	va_copy (args2, args);
	cur = flag_dot_len(str, args2);
	print = 0;
	print2 = 0;
	while (*str == '.')
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
			// /format_check(str, args, i);
			return (str + 1);
	}
	if (cur != 0 && ft_atoi(str) >= cur)
		print = ft_atoi (str) - cur;
	else
		print2 = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == 'd' || *str == 'i')
	{
		format_check_zero(str, args, i, print);
		str++;
		return (str);
	}
	while (print--)
		ft_putchar_fd('0', 1, i);
	if (print != 0)
		format_check_dot(str, args, i, print2);
	else
		format_check_dot(str, args, i, print);
	str++;
	return (str);
}