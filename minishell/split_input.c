#include "minishell.h"

char	*fill_cmd(char **arg, int sq, int dq, int cb)
{
	char	*arr;
	int		j;
    int     p;

	j = 0;
    p = 0;
	arr = malloc(sizeof(char) * (ft_strlen(*arg) + 1));
	if (!arr)
		return (NULL);
	while ((**arg) && ((**arg) != ' ' || sq || dq || cb || p))
	{
		if (!cb && !dq && (**arg) == '\'')
			sq = !sq;
		else if (!cb && !sq && (**arg) == '"')
			dq = !dq;
		else if ((**arg) == '\\')
			(*arg)++;
		arr[j++] = (**arg);
		if ((**arg) == '{' || (**arg) == '}')
			cb = !cb;
        if ((**arg) == '(' || (**arg) == ')')
            p = !p;
		(*arg)++;
	}
	return (arr[j] = '\0', arr);
}

char	**cmds_handler(char *arg)
{
	char	**cmds;
	int		single_quote;
	int		double_quote;
	int		cbracket;
	int		i;

	single_quote = 0;
	double_quote = 0;
	cbracket = 0;
	i = 0;
	cmds = malloc(sizeof(char *) * (ft_strlen(arg) + 1));
	if (!cmds)
		return (ft_error_handling("malloc"), NULL);
	while (*arg)
	{
		while (*arg && *arg == ' ')
			arg++;
		if (*arg && *arg != ' ')
		{
			cmds[i++] = fill_cmd(&arg, single_quote, double_quote, cbracket);
			if (!cmds[i - 1])
				return (ft_free_2d(&cmds), ft_error_handling("malloc"), NULL);
		}
	}
	return (cmds[i] = NULL, cmds);
}