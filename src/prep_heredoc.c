/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:09:33 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/15 12:30:12 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ctrl_d_msg(char *redir)
{
	write(2, "warning: here-document delimited", 32);
	write(2, " by end-of-file (wanted `", 26);
	write(2, redir, ft_strlen(redir));
	write(2, "')\n", 3);
}
static void ctrlc_hd(int signal)
{
	(void)signal;

	write(2, "\n", 1);
	free_global_main_cmd();
	clear_cmd_table(g_data->global_table);
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

static void	signal_heredoc_on (void)
{
	signal(SIGINT, ctrlc_hd);
}

static void	wait_children(void)
{
	int	wstatus;

	waitpid(-1, &wstatus, 0);
	g_data->exit_code = WEXITSTATUS(wstatus);
	return ;
}

static void	process_heredoc(char *redir, int n_cmd, int *fd)
{
	char	*s;
	char	*n_cmd_str;
	pid_t 	pid;

	pid = fork();
	if (pid < 0)
		error("fork", 0);
	if (pid > 0)
		signal(SIGINT, ctrlc_parent_hd);
	if (pid == 0)
	{
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
		free_global_main_cmd();
		clear_cmd_table(g_data->global_table);
		clear_data();
		exit(0);
	}
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
	t_cmd	*cmd_table;

	i = -1;
	while (cmds[++i])
	{
		cmd_table = make_cmd_table(cmds[i]);
		open_heredoc(cmd_table->redirections, i);
		clear_cmd_table (cmd_table);
	}
}
