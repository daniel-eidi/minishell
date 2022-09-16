/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:24:49 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/13 14:42:30 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<minishell.h>

static void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

void	process_quotes2(char *line)
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
		line[i - p] = line[i];
		p += (!s && (line[i] == 34)) || (!d && (line[i] == 39));
		if ((line[i] == 39) && !d)
			s = !s;
		if ((line[i] == 34) && !s)
			d = !d;
	}
	line[i - p] = line[i];
}

char	**token_line(char *line)
{
	char	**split;
	int	i;

	process_quotes(line);
	split = ft_split(line, ' ');
	printf("saída da split:\n");
	i = -1;
	while(split[++i])
	{
	process_quotes2(split[i]);
		ft_printf("%s\n", split[i]);
	}
	
	restore_spaces(split);
	free_ptr((void *)&line);
	return (split);
}
