/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:52:47 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 15:55:07 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	before_fork(char **cmd, t_pids_pipes **pid_pipe)
{
	int total_cmd;

	total_cmd = 0;
	while (cmd[total_cmd])
		total_cmd = total_cmd + 1;
	//*pid_pipe = malloc(sizeof(t_pids_pipes));
	(*pid_pipe)->pipes = create_pipes(total_cmd);
		dprintf(2, "pid_pipe->pipes[0] = %p\n", (*pid_pipe)->pipes[0]);
	(*pid_pipe)->pids = create_pids(total_cmd);
	(*pid_pipe)->total_cmd = total_cmd;
}
