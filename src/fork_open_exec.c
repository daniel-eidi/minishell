/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:55:34 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/30 19:34:29 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	open_fds(char **redir, t_pids_pipes *aux, int n_cmd, bool *have_outfile)
{
	int	fd[2];
	int	i;
	char	*s;
	char	*n_cmd_str;
	char	*limiter;
	char	*name;

	i = -1;
	while (redir[++i])
	{
		if (ft_strcmp (redir[i], ">>") == 0)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_ok(redir[++i], O_WRONLY | O_CREAT | O_APPEND, 1);
			//*out = fd[1];
			aux->pipes[n_cmd + 1][1] = fd[1];
			*have_outfile = true;
		}
		if (ft_strcmp (redir[i], ">") == 0)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_ok(redir[++i], O_WRONLY | O_CREAT | O_TRUNC, 1);
			//*out = fd[1];
			aux->pipes[n_cmd + 1][1] = fd[1];
			*have_outfile = true;
		}
		if (ft_strcmp (redir[i], "<") == 0)
		{
			if (fd[0])
				close(fd[0]);
			fd[0] = open_ok(redir[++i], O_RDONLY, 0);
			//*in = fd[0];
			aux->pipes[n_cmd][0] = fd[0];
		}
		if(ft_strcmp (redir[i], "<<") == 0)
		{
			if (fd[0])
				close(fd[0]);
			n_cmd_str = ft_itoa(n_cmd);
			name = ft_strjoin("/tmp/inputfile", n_cmd_str);
			free(n_cmd_str);
			fd[0] = open_ok(name, O_WRONLY | O_CREAT | O_TRUNC, 0);
			limiter = ft_strjoin(redir[++i], "\n");
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
	}
}

void	fork_open_exec( char *cmd, int n_cmd, t_pids_pipes *aux)
{
	t_cmd	*cmd_table;
	bool	have_outfile;

	have_outfile = false;
	aux->pids[n_cmd] = fork();
	if (aux->pids[n_cmd] < 0)
		error("fork", 0);
	if (aux->pids[n_cmd] == 0)
	{
		cmd_table = make_cmd_table(cmd);
		close_pipes(aux->total_cmd, aux->pipes, n_cmd);
		open_fds(cmd_table->redirections, aux, n_cmd, &have_outfile);
		dup2(aux->pipes[n_cmd][0], STDIN_FILENO);
		if (n_cmd != (aux->total_cmd - 1) || have_outfile)
			dup2(aux->pipes[(n_cmd + 1)][1], STDOUT_FILENO);
		close(aux->pipes[n_cmd][0]);
		close(aux->pipes[(n_cmd + 1)][1]);
		free_ptr((void **) aux->pipes);
		if (!is_builtin(cmd_table->cmd_and_args))
			exec_cmd(cmd_table->cmd_and_args);
		return (run_builtin(cmd_table->cmd_and_args));
	}
}

static int	len_hash(void)
{
	int		i;
	int		len;
	t_list	*aux;

	i = -1;
	len = 0;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			if (((t_item *) aux->content)->key != NULL)
				len++;
			aux = aux->next;
		}
	}
	return (len);
}

static void	join_key_value(t_item *item, char	**join, int *j)
{	
	if (item->key != NULL)
	{
		*join = ft_strjoin(item->key, "=");
		*join = ft_strnjoin(*join, item->value, ft_strlen(item->value));
		*j = *j + 1;
	}
}

static char	**convert_hash_arr(void)
{
	t_list	*aux;
	int		i;
	int		len;
	char	**environ;
	int		j;

	i = -1;
	len = len_hash();
	environ = malloc(sizeof(char *) * (len + 1));
	environ[len] = NULL;
	i = -1;
	j = 0;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			join_key_value((t_item *) aux->content, &environ[j], &j);
			aux = aux->next;
		}
	}
	return (environ);
}

void	exec_cmd(char **args)
{
	char		*cmd_path;
	t_list		*temp;
	char		**environ;

	environ = convert_hash_arr();
	temp = find_entry("PATH", g_data->hash_table);
	if (*args[0] == '/' || *args[0] == '.' || *args[0] == '~')
		cmd_path = find_absolute_path(args[0]);
	else
	{
		if (temp == NULL)
		{
			ft_putstr_fd("Error: path not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		cmd_path = get_path(&args[0], ((t_item *)temp->content)->value);
	}
	//dprintf(2,"cmd 0 = %s in pid %d\n", cmd_path, getpid());
	execve(cmd_path, args, environ);
}
