/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:16:16 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/17 10:40:58 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	await_all_children(int children_count, pid_t *pid)
{
	int	i;
	int	wstatus;
	int	pid_returned;
	int	lst_cmd_status;

	i = -1;
	lst_cmd_status = -1;
	while (children_count && ++i <= children_count)
	{
		pid_returned = waitpid(-1, &wstatus, 0);
		if (pid_returned == pid[children_count - 1] && WIFEXITED(wstatus))
			lst_cmd_status = WEXITSTATUS(wstatus);
	}
	if (lst_cmd_status >= 0)
		g_data->exit_code = lst_cmd_status;
	return ;
}

void	after_fork(int n_cmd, int **pipes, pid_t *pid)
{
	close_pipes_main(n_cmd, pipes);
	await_all_children(n_cmd, pid);
	if (pipes[0])
		close(pipes[0][1]);
	close(pipes[n_cmd][0]);
	free_ptr((void *) &pid);
	free_split((void **)pipes);
	free(pipes);
}
