/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:51:27 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 18:45:01 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_data_after_exec_cmd(char **environ)
{
	free_pids_and_pipes(g_data->aux);
	free_split((void **) environ);
	free(environ);
	clear_data();
}

void	if_absolute_path(t_list *temp, char **environ, \
							char **args, char **cmd_path)
{
	if (temp == NULL)
	{
		free_data_after_exec_cmd(environ);
		error_fork("Error: path not found\n", 127);
	}
	*cmd_path = get_path(&args[0], ((t_item *)temp->content)->value);
	if (!(*cmd_path))
	{
		write(2, args[0], ft_strlen(args[0]));
		free_data_after_exec_cmd(environ);
		error_fork(": command not found\n", 127);
	}
}

void	free_cmd_and_close_pipes(char **cmd, int n_cmd, t_pids_pipes *aux)
{
	free_split((void **)cmd);
	free(cmd);
	close_pipes(aux->total_cmd, aux->pipes, n_cmd);
}
