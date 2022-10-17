/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:50:19 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/17 11:06:16 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ctrl_d_msg(char *redir)
{
	write(2, "warning: here-document delimited", 32);
	write(2, " by end-of-file (wanted `", 26);
	write(2, redir, ft_strlen(redir));
	write(2, "')\n", 3);
}

void	ctrlc_hd(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	free_global_main_cmd();
	free_pids_and_pipes(g_data->aux);
	clear_data();
	exit (130);
}

void	ctrlc_parent_hd(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_data->exit_code = 130;
		g_data->not_run = 1;
	}
}

void	signal_heredoc_on(void)
{
	signal(SIGINT, ctrlc_hd);
}

void	wait_children(void)
{
	int	wstatus;

	waitpid(-1, &wstatus, 0);
	g_data->exit_code = WEXITSTATUS(wstatus);
	return ;
}
