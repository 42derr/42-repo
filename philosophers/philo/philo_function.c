#include "philo.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		cm;
	int		i;

	cm = c % 256;
	str = (char *) s;
	i = 0;
	while (s[i] != cm && s[i] != '\0')
		i++;
	if (s[i] == cm)
		return (str + i);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	i;
	long	s;
	long	m;

	i = 0;
	m = 1;
	s = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = m * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		s = s * 10 + (nptr[i] - 48);
		i++;
	}
	s = s * m;
	if (s <= 2147483647 && s >= -2147483648)
		return ((int)s);
	return (0);
}