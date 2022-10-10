/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:16 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 11:24:12 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	first_argument_not_numeric(char **cmd)
{
	int	i;

	if ((!cmd) || (cmd && !cmd[1]))
		return (0);
	i = -1;
	while (cmd && cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			write(2, "exit: ", 6);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, ": numeric argument required\n", 28);
			g_data->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

void exit_minishell(t_cmd *cmd_table, t_pids_pipes *aux)
{
	char	**cmd;
	int		s;
	int		n;

	printf("exit\n");
	if (cmd_table == NULL)
		exit (0);
	cmd = cmd_table->cmd_and_args;
	n = first_argument_not_numeric(cmd);
	if (!n)
	{
		if (cmd && (cmd[2]))
		{
			write(2, "exit : too many arguments\n", 26);
			g_data->exit_code = 1;
			return ;
		}
	}
	if (!cmd)
		exit(0);
	free_and_exit(aux);
	if (cmd[1])
	{
		if (n)
			s = 2;
		else
			s = ft_atoi(cmd[1]);
	}
	else
		s = 0;
	clear_cmd_table(cmd_table);
	exit (s);
}