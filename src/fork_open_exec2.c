/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:35:59 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/18 11:03:40 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_heredoc_fork(t_pids_pipes *aux, int n_cmd, \
								int *fd, int *have_file)
{
	char	*n_cmd_str;
	char	*name;

	if (fd[0])
		close(fd[0]);
	n_cmd_str = ft_itoa(n_cmd);
	name = ft_strjoin("/tmp/inputfile", n_cmd_str);
	free(n_cmd_str);
	fd[0] = open_ok_fork(name, O_RDONLY, 0);
	aux->pipes[n_cmd][0] = fd[0];
	if (*have_file == 2 || *have_file == 3)
		*have_file = 3;
	else
		*have_file = 1;
	free(name);
}

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
	free(name);
}

void	open_fdsfrk(char **redir, t_pids_pipes *aux, int n_cmd, int *have_file)
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
			fd[1] = open_ok_fork(redir[++i], flags, 1);
			aux->pipes[n_cmd + 1][1] = fd[1];
		}
		if (ft_strcmp (redir[i], "<") == 0)
		{
			set_infile_flags(fd, redir[i], &flags, have_file);
			fd[0] = open_ok_fork(redir[++i], O_RDONLY, 0);
			aux->pipes[n_cmd][0] = fd[0];
		}
		if (ft_strcmp (redir[i], "<<") == 0)
			get_heredoc_fork(aux, n_cmd, fd, have_file);
	}
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

void	print_error_on_failed_execve(char *cmd_path)
{
	dprintf(2, "cmd_path dentro da print error = %s\n", cmd_path);
	write(2, cmd_path, ft_strlen(cmd_path));
	if (chdir(cmd_path) == 0)
		write(2, ": Is a directory\n", 18);
	else
		write(2, ": no such file or directory\n", 28);	
}