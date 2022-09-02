/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:24:49 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/01 13:20:34 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>


char	*treat_line(char *cmd)
{
	char	*arg;
	//char	**split;
	char	inside;
	int		i;

	arg = ft_calloc(ft_strlen(cmd) + 1, 1);
	inside = 0;
	i = 0;
	while (*cmd)
	{
		if ((*cmd == '\'' || *cmd == '\"') && inside == 0)
			inside = *cmd ;
		else if (inside != 0 && *cmd == inside)
			inside = 0;
		else if (inside != 0 && *cmd == ' ')
			arg[i++] = -1;
		else
			arg[i++] = *cmd;
		cmd++;
	}
	//split = ft_split(arg, ' ');
	//free(arg);
	//restore_spaces(split);
	return (arg);
}

char	*space_arg(char *cmd, char *c)
{
	char	*arg;
	//char	**split;
//	char	inside;
	int		i;

	arg = ft_calloc(ft_strlen(cmd) + 1, 1);
//	inside = 0;
	i = 0;
	while (*cmd)
	{
		if (!ft_strncmp(cmd, c, 1) && !ft_strncmp(cmd + 1, c, 1))
		{
			arg[i++] = ' ';
			arg[i++] = *cmd;
			arg[i++] = *cmd;
			arg[i++] = ' ';
			cmd = cmd + 2;
		}
		else if (!ft_strncmp(cmd, c, 1) && ft_strncmp(cmd + 1, c, 1))
		{
			arg[i++] = ' ';
			arg[i++] = *cmd;
			arg[i++] = ' ';
			cmd++;
		}
		arg[i++] = *cmd;	
		cmd++;
	}
	//split = ft_split(arg, ' ');
	//free(arg);
	//restore_spaces(split);
	return (arg);
}
