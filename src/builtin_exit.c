/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:16 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/07 13:23:27 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exit_minishell(t_cmd *cmd_table, t_pids_pipes *aux)
{
	char	**cmd;
	int		s;

	printf("exit\n");
	if (cmd_table == NULL)
		exit (0);
	cmd = cmd_table->cmd_and_args;
	if (cmd && (cmd[2]))
	{
		write(2, "exit : too many arguments\n", 26);
		g_data->exit_code = 1;
		return ;
	}
	if (!cmd)
		exit(0);
	free_and_exit(aux);
	if (cmd[1])
		s = ft_atoi(cmd[1]);
	else
		s = 0;
	clear_cmd_table(cmd_table);
	exit (s);
}