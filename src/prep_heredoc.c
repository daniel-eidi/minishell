/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:09:33 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/17 11:06:44 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_exit_child_hd(void)
{
	free_global_main_cmd();
	free_pids_and_pipes(g_data->aux);
	clear_data();
	exit(0);
}

static void	child_heredoc(char *redir, int n_cmd, int *fd)
{
	char	*n_cmd_str;
	char	*s;

	signal_heredoc_on();
	if (fd[0])
		close(fd[0]);
	n_cmd_str = ft_itoa(n_cmd);
	s = ft_strjoin("/tmp/inputfile", n_cmd_str);
	free(n_cmd_str);
	fd[0] = open_ok(s, O_WRONLY | O_CREAT | O_TRUNC, 1);
	free(s);
	s = readline("> ");
	while (s != NULL && ft_strcmp(s, redir))
	{
		write(fd[0], s, ft_strlen(s));
		write(fd[0], "\n", 1);
		free(s);
		s = readline("> ");
	}
	if (!s)
		ctrl_d_msg(redir);
	close(fd[0]);
	free(s);
	free_exit_child_hd();
}

static void	process_heredoc(char *redir, int n_cmd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error("fork", 0);
	if (pid > 0)
		signal(SIGINT, ctrlc_parent_hd);
	if (pid == 0)
		child_heredoc(redir, n_cmd, fd);
	wait_children();
}

static void	open_heredoc(char **redir, int n_cmd)
{
	int	fd[2];
	int	i;

	fd[0] = 0;
	fd[1] = 0;
	i = -1;
	while (redir[++i])
	{
		if (ft_strcmp (redir[i], "<<") == 0 && redir[i + 1] && !g_data->not_run)
			process_heredoc(redir[++i], n_cmd, fd);
	}
}

void	prepare_heredoc(char **cmds)
{
	int		i;

	i = -1;
	while (cmds[++i])
	{
		g_data->global_table = make_cmd_table(cmds[i]);
		open_heredoc(g_data->global_table->redirections, i);
		clear_cmd_table (g_data->global_table);
	}
}
