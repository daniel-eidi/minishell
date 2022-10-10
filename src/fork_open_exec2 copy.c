/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:35:59 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 15:09:13 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_heredoc(t_pids_pipes *aux, int n_cmd, int *fd, int *have_file)
{
	char	*n_cmd_str;
	char	*name;

	if (fd[0])
		close(fd[0]);
	n_cmd_str = ft_itoa(n_cmd);
	name = ft_strjoin("/tmp/inputfile", n_cmd_str);
	free(n_cmd_str);
	fd[0] = open_ok(name, O_RDONLY, 0);
	aux->pipes[n_cmd][0] = fd[0];
	if (*have_file == 2 || *have_file == 3)
		*have_file = 3;
	else
		*have_file = 1;
}

static void	set_outfile_flags(int *fd, char *redir, int *flags, int *have_file)
{
	if (fd[1])
		close(fd[1]);
	if (ft_strcmp (redir, ">>") == 0)
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	if (ft_strcmp (redir, ">") == 0)
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (*have_file == 1 || *have_file == 3)
		*have_file = 3;
	else
		*have_file = 2;
}

static void	set_infile_flags(int *fd, char *redir, int *flags, int *have_file)
{
	if (fd[0])
		close(fd[0]);
	if (ft_strcmp (redir, "<") == 0)
		*flags = O_RDONLY;
	if (*have_file == 2 || *have_file == 3)
		*have_file = 3;
	else
		*have_file = 1;
}

void	open_fds(char **redir, t_pids_pipes *aux, int n_cmd, int *have_file)
{
	int	fd[2];
	int	i;
	int	flags;

	fd[0] = 0;
	fd[1] = 0;
	i = -1;
	while (redir[++i])
	{
		if (redir[i][0] == '>')
		{
			set_outfile_flags(fd, redir[i], &flags, have_file);
			fd[1] = open_ok(redir[++i], flags, 1);
			aux->pipes[n_cmd + 1][1] = fd[1];
		}
		if (ft_strcmp (redir[i], "<") == 0)
		{
			set_infile_flags(fd, redir[i], &flags, have_file);
			fd[0] = open_ok(redir[++i], O_RDONLY, 0);
			aux->pipes[n_cmd][0] = fd[0];
		}
		if (ft_strcmp (redir[i], "<<") == 0)
			get_heredoc(aux, n_cmd, fd, have_file);
	}
}
