#include <minishell.h>

void	process_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	d = 0;
	s = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == '$') && !s)
			line[i] = -2;
		if ((line[i] == ' ') && (s || d))
			line[i] = -1;
		if ((line[i] == 39) && !d)
			s = !s;
		if ((line[i] == 34) && !s)
			d = !d;
	}
}
