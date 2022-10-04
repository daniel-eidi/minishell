/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:49:28 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/04 14:32:17 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	await_all_children(int children_count, pid_t *pid)
{
	int	i;
	int	wstatus;
	int	pid_returned;

	i = -1;
	while (++i <= children_count)
	{
		pid_returned = waitpid(-1, &wstatus, 0);
		if (pid_returned == pid[children_count - 1])
			g_data->exit_code = WEXITSTATUS(wstatus);
	}
	//g_data->exit_code = WEXITSTATUS(wstatus);
	return ;
}

void	after_fork(int n_cmd, int **pipes, pid_t *pid)
{
	close_pipes_main(n_cmd, pipes);
	await_all_children(n_cmd, pid);
	close(pipes[0][1]);
	close(pipes[n_cmd][0]);
	free_ptr((void *) &pid);
	free_split((void **)pipes);
	free(pipes);
}
