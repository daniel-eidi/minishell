/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:51:27 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/11 18:00:02 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_data_after_exec_cmd(char **environ)
{
	free_pids_and_pipes(g_data->aux);
	if (environ)
	{
		free_split((void **) environ);
		free(environ);
	}
	clear_data();
}

void	if_absolute_path(t_list *temp, char **environ, \
							char **args, char **cmd_path)
{
	if (temp == NULL)
	{
		free_data_after_exec_cmd(environ);
		error_fork("Error: path not found\n", 127);
	}
	*cmd_path = get_path(&args[0], ((t_item *)temp->content)->value);
	if (!(*cmd_path))
	{
		write(2, args[0], ft_strlen(args[0]));
		free_data_after_exec_cmd(environ);
		error_fork(": command not found\n", 127);
	}
}

void	free_cmd_and_close_pipes(char **cmd, int n_cmd, t_pids_pipes *aux)
{
	free_split((void **)cmd);
	free(cmd);
	close_pipes(aux->total_cmd, aux->pipes, n_cmd);
}

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
