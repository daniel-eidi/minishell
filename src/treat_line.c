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

static char	*space_arg(char **s, char *cmd, char *c, int *i)
{
	char	*arg;

	arg = *s;
	if (!ft_strncmp(&cmd[*i], c, 1) && !ft_strncmp(&cmd[*i + 1], c, 1))
	{
		arg = ft_strnjoin(arg, " ", 1);
		arg = ft_strnjoin(arg, &cmd[*i], 1);
		arg = ft_strnjoin(arg, &cmd[*i], 1);
		arg = ft_strnjoin(arg, " ", 1);
		*i = *i + 2;
	}
	else if (!ft_strncmp(&cmd[*i], c, 1) && ft_strncmp(&cmd[*i +1], c, 1))
	{
		arg = ft_strnjoin(arg, " ", 1);
		arg = ft_strnjoin(arg, &cmd[*i], 1);
		arg = ft_strnjoin(arg, " ", 1);
		*i = *i + 1;
	}
	return (arg);
}

static char	*check_spaces(char **s, char *line, int *i, char inside)
{
	char	*arg;

	arg = *s;
	if (inside == 0)
	{
		arg = space_arg(&arg, line, ">", i);
		arg = space_arg(&arg, line, "<", i);
		arg = space_arg(&arg, line, "|", i);
		arg = space_arg(&arg, line, "&", i);
	}
	return (arg);
}

char	*treat_line(char *line)
{
	char	*arg;
	char	inside;
	int		i;
	char	change;

	arg = ft_strdup("");
	inside = 0;
	change = -1;
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '\"') && inside == 0)
			inside = line[i];
		else if (inside != 0 && line[i] == inside)
			inside = 0;
		else if (inside != 0 && line[i] == ' ')
		{
			arg = ft_strnjoin(arg, &change, 1);
			i++;
		}
		else
			arg = check_spaces(&arg, line, &i, inside);
		arg = ft_strnjoin(arg, &line[i++], 1);
	}
	return (arg);
}

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

char	**token_line(char *line)
{
	char	*token;
	char	**split;

	token = treat_line(line);
	split = ft_split(token, ' ');
	restore_spaces(split);
	free_ptr((void *)&token);
	free_ptr((void *)&line);
	return (split);
}
