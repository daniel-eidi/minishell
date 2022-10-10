/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:39:10 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 15:11:14 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char **cmd)
{
	if (!cmd[0])
		return (0);
	if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "pwd") \
	|| !ft_strcmp(cmd[0], "env"))
		return (1);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") \
	|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
		return (2);
	return (0);
}

void	run_builtin_fork(t_cmd *cmd_table, t_pids_pipes *aux)
{
	char	**cmd;

	cmd = cmd_table->cmd_and_args;
	if (!ft_strcmp(cmd[0], "cd" ))
		builtin_cd(cmd);
	if (!ft_strcmp(cmd[0], "echo" ))
		builtin_echo(cmd);
	if (!ft_strcmp(cmd[0], "pwd" ))
		builtin_pwd();
	if (!ft_strcmp(cmd[0], "export" ))
		builtin_export(cmd);
	if (!ft_strcmp(cmd[0], "env" ))
		builtin_env();
	if (!ft_strcmp(cmd[0], "unset" ))
		builtin_unset(cmd);
	if (!ft_strcmp(cmd[0], "exit" ))
		exit_minishell(cmd_table, aux);
	free_pids_and_pipes(aux);
	clear_data();
}

void	run_builtin(t_cmd *cmd_table, t_pids_pipes *aux)
{
	char	**cmd;

	cmd = cmd_table->cmd_and_args;
	if (!ft_strcmp(cmd[0], "cd" ))
		builtin_cd(cmd);
	if (!ft_strcmp(cmd[0], "echo" ))
		builtin_echo(cmd);
	if (!ft_strcmp(cmd[0], "pwd" ))
		builtin_pwd();
	if (!ft_strcmp(cmd[0], "export" ))
		builtin_export(cmd);
	if (!ft_strcmp(cmd[0], "env" ))
		builtin_env();
	if (!ft_strcmp(cmd[0], "unset" ))
		builtin_unset(cmd);
	if (!ft_strcmp(cmd[0], "exit" ))
		exit_minishell(cmd_table, aux);
}
