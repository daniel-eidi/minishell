/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 23:24:49 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/27 16:59:17 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<minishell.h>

// static void	restore_spaces(char **exec_args)
// {
// 	char	*str;

// 	while (*exec_args)
// 	{
// 		str = *exec_args;
// 		while (*str)
// 		{
// 			if (*str == -1)
// 				*str = ' ';
// 			str++;
// 		}
// 		exec_args++;
// 	}
// 	return ;
// }

static void	restore_char(char **exec_args, char find, char change)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == find)
				*str = change;
			str++;
		}
		exec_args++;
	}
	return ;
}

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
	arg = ft_strnjoin(arg, &line[*i], 1);
	return (arg);
}


char	*treat_line(char *line)
{
	char	*arg;
	char	inside;
	int		i;

	arg = ft_strdup("");
	inside = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '\"') && inside == 0)
					inside = line[i];
		else if (inside != 0 && line[i] == inside)
					inside = 0;
		arg = check_spaces(&arg, line, &i, inside); //insere espaços redirecionadores
		i++;
	}
	return (arg);
}

char	**token_line(char *line)
{
	char	**split;
	char	*str;
	int	i;

	printf("before treat_li = %s\n", line);
	str = treat_line(line);
	printf("treat_line      = %s\n", str);
	process_quotes(str);  //troca $, e espaços ou | dentro de aspas , -2 , -1 e -3 respectivamente.
	printf("processe quotes = %s\n", str);
	split = ft_split(str, '|');
	//	i = -1;
	//	while (split[++i])
	//	printf("split[%d] = %s\n", i, split[i]);
	//printf("saída da split:\n");
	i = -1;
	while(split[++i])
	{
		process_quotes2(split[i]); //remove aspas duplas e simples
		//ft_printf("%s\n", split[i]);
	}
	//printf("endereço = %p\n", &restore_spaces);
	restore_char(split, -3, '|');
	free_ptr((void *)&line);
	free_ptr((void *)&str);
	return (split);
}
