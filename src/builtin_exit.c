/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:16 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/18 10:13:31 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	first_argument_not_numeric(char **cmd)
{
	int	i;

	if ((!cmd) || (cmd && !cmd[1]))
		return (0);
	i = -1;
	if (cmd && ((cmd[1][0] == '+') || (cmd && cmd[1][0] == '-')))
		i++;
	while (cmd && cmd[1][++i])
	{
		if ((invalid_uatoi(cmd[1])) || (!ft_isdigit(cmd[1][i])))
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

int	set_exit_code(char **cmd, int n)
{
	int	s;

	if (cmd[1])
	{
		if (n)
			s = 2;
		else
			s = ft_uatoi(cmd[1]);
	}
	else
		s = 0;
	return (s);
}

void	free_global_main_cmd(void)
{
	free_split((void **)g_data->main_cmd);
	free_ptr((void *)&g_data->main_cmd);
}

void	exit_minishell(t_cmd *cmd_table, t_pids_pipes *aux)
{
	char	**cmd;
	int		n;
	int		s;

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
	s = set_exit_code(cmd, n);
	free_global_main_cmd();
	free_and_exit(aux);
	clear_cmd_table(cmd_table);
	exit (s);
}
