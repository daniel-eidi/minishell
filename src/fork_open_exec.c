/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:55:34 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 15:07:42 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_cmd(t_cmd *cmd_table);

void	fork_open_exec(char **cmd, int n_cmd, t_pids_pipes *aux)
{
	int		have_file;

	have_file = 0;
	signal(SIGINT, ctrlc_fork);
	signal(SIGQUIT, ctrlc_fork);
	aux->pids[n_cmd] = fork();
	if (aux->pids[n_cmd] < 0)
		error("fork", 0);
	if (aux->pids[n_cmd] == 0)
	{
		signal_for_child();
		g_data->global_table = make_cmd_table(cmd[n_cmd]);
		free_split((void **)cmd);
		free(cmd);
		close_pipes(aux->total_cmd, aux->pipes, n_cmd);
		open_fds(g_data->global_table->redirections, aux, n_cmd, &have_file);
		if (n_cmd != 0 || have_file == 1 || have_file == 3)
			dup2(aux->pipes[n_cmd][0], STDIN_FILENO);
		if (n_cmd != (aux->total_cmd - 1) || have_file > 1)
			dup2(aux->pipes[(n_cmd + 1)][1], STDOUT_FILENO);
		close(aux->pipes[n_cmd][0]);
		close(aux->pipes[(n_cmd + 1)][1]);
		if (!is_builtin(g_data->global_table->cmd_and_args))
			exec_cmd(g_data->global_table);
		run_builtin_fork(g_data->global_table, aux);
		exit (0);
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

void	exec_cmd(t_cmd *cmd_table)
{
	char		*cmd_path;
	t_list		*temp;
	char		**environ;
	char		**args;

	args = cmd_table->cmd_and_args;
	environ = convert_hash_arr();
	temp = find_entry("PATH", g_data->hash_table);
	if (*args[0] == '/' || *args[0] == '.' || *args[0] == '~')
		cmd_path = find_absolute_path(args[0]);
	else
	{
		if (temp == NULL)
		{
			free_pids_and_pipes(g_data->aux);
			free_split((void **) environ);
			free(environ);
			clear_data();
			error_fork("Error: path not found\n", 127);
		}
		if (!(cmd_path = get_path(&args[0], ((t_item *)temp->content)->value)))
		{
			write(2, args[0], ft_strlen(args[0]));
			free_pids_and_pipes(g_data->aux);
			free_split((void **) environ);
			free(environ);
			clear_data();
			error_fork(": command not found\n", 127);
		}
	}
	if (execve(cmd_path, args, environ) == -1)
	{
		write(1, cmd_path, ft_strlen(cmd_path));
		write(1, ": no such file or directory\n", 28);
		free(cmd_path);
		free_split((void **) environ);
		free(environ);
	}
}
