/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:35:59 by mgaldino          #+#    #+#             */
/*   Updated: 2022/09/30 17:39:04 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	process_heredoc(char *redir, t_pids_pipes *aux, int n_cmd, int *fd)
{
	char	*s;
	char	*n_cmd_str;
	char	*limiter;
	char	*name;

	if (fd[0])
		close(fd[0]);
	n_cmd_str = ft_itoa(n_cmd);
	name = ft_strjoin("/tmp/inputfile", n_cmd_str);
	free(n_cmd_str);
	fd[0] = open_ok(name, O_WRONLY | O_CREAT | O_TRUNC, 0);
	limiter = ft_strjoin(redir, "\n");
	write(1, "> ", 2);
	s = get_next_line(STDIN_FILENO);
	while (ft_strcmp(s, limiter))
	{
		write(fd[0], s, ft_strlen(s));
		free(s);
		write(1, "> ", 2);
		s = get_next_line(STDIN_FILENO);
	}
	close(fd[0]);
	fd[0] = open_ok(name, O_RDONLY, 0);
	aux->pipes[n_cmd][0] = fd[0];
}

void	set_outfile_flags(int *fd, char *redir, int *flags, bool *have_outfile)
{
	if (fd[1])
		close(fd[1]);
	if (ft_strcmp (redir, ">>") == 0)
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	if (ft_strcmp (redir, ">") == 0)
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
	*have_outfile = true;
}

void	open_fds(char **redir, t_pids_pipes *aux, int n_cmd, bool *have_outfile)
{
	int	fd[2];
	int	i;
	int	flags;
	
	fd[0] = 0;
	fd[1] = 0;
	i = -1;
	while (redir[++i])
	{
		dprintf(2, "open_fds\n");
		if (redir[i][0] == '>')
		{
			set_outfile_flags(fd, redir[i], &flags, have_outfile);
			fd[1] = open_ok(redir[++i], flags, 1);
			aux->pipes[n_cmd + 1][1] = fd[1];
		}
		if (ft_strcmp (redir[i], "<") == 0)
		{
			if (fd[0])
				close(fd[0]);
			fd[0] = open_ok(redir[++i], O_RDONLY, 0);
			aux->pipes[n_cmd][0] = fd[0];
		}
		if (ft_strcmp (redir[i], "<<") == 0)
			process_heredoc(redir[++i], aux, n_cmd, fd);
	}
}
