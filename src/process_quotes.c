#include <minishell.h>

void	process_quotes(char *line)
{
	int	i;
	int	p;
	int	s;
	int	d;

	d = 0;
	s = 0;
	p = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == '$') && !s)
			line[i] = -2;
		line[i - p] = line[i];
		p += (!s && (line[i] == 34)) || (!d && (line[i] == 39));
		if ((line[i] == 39) && !d)
			s = !s;
		if ((line[i] == 34) && !s)
			d = !d;
	}
	line[i - p] = line[i];
}
