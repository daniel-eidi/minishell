/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:49:28 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/03 17:36:43 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	await_all_children(int children_count)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i <= children_count)
		waitpid(-1, &wstatus, 0);
	g_data->exit_code = WEXITSTATUS(wstatus);
	return ;
}

void	after_fork(int n_cmd, int **pipes, pid_t *pid)
{
	close_pipes_main(n_cmd, pipes);
	await_all_children(n_cmd);
	close(pipes[0][1]);
	close(pipes[n_cmd][0]);
	free_ptr((void *) &pid);
	free_split((void **)pipes);
	free(pipes);
}
