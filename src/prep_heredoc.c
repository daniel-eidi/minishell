/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:09:33 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 14:55:43 by daeidi-h         ###   ########.fr       */
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

static void	process_heredoc(char *redir, int n_cmd, int *fd)
{
	char	*s;
	char	*n_cmd_str;

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
		if (ft_strcmp (redir[i], "<<") == 0)
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
