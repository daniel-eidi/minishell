/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:52:47 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/29 20:06:45 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	before_fork(char **cmd, t_pids_pipes **pid_pipe)
{
	int total_cmd;

	total_cmd = 0;
	while (cmd[total_cmd])
		total_cmd = total_cmd + 1;
	*pid_pipe = malloc(sizeof(t_pids_pipes));
	(*pid_pipe)->pipes = create_pipes(total_cmd);
	(*pid_pipe)->pids = create_pids(total_cmd);
	(*pid_pipe)->total_cmd = total_cmd;
}
