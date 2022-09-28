/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_open_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:55:34 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/28 23:16:53 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

//executamos o makecmd;
//contamos quantos comandos totais;
// criamos pipes e pids;

void	before_fork(char **cmd, int *total_cmd, int	***pipes, pid_t	**pid)
{
	*total_cmd = 0;
	while(cmd[*total_cmd])
		*total_cmd = *total_cmd + 1;
	//printf("total cmd = %d\n", *total_cmd);		
	*pipes = create_pipes(*total_cmd);
	*pid = create_pids(*total_cmd);	
}

static void	open_fds(char **redir, int *in, int *out, bool *have_outfile)
{
	int fd[2];
	int i;
	
	//dprintf(2, "ANTES --- in = %d e out = %d\n", *in, *out);
	i = -1;
	while (redir[++i])
	{
		if(ft_strcmp (redir[i], ">>") == 0)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_ok(redir[++i], O_WRONLY | O_CREAT | O_APPEND, 1);
			*out = fd[1];
			*have_outfile = true;
		}
		if(ft_strcmp (redir[i], ">") == 0)
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = open_ok(redir[++i], O_WRONLY | O_CREAT | O_TRUNC, 1);
			*out = fd[1];
			*have_outfile = true;
		}
		if(ft_strcmp (redir[i], "<") == 0)
		{
			if (fd[0])
				close(fd[0]);
			fd[0] = open_ok(redir[++i], O_RDONLY, 0);
			*in = fd[0];
		}
	}
	//dprintf(2, " in = %d e out = %d\n", *in, *out);
}

void	fork_open_exec( char *cmd, int n_cmd, int total_cmd, int **pipes, pid_t pid)
{
	t_cmd	*cmd_table;
	bool	have_outfile;
	
	have_outfile = false;
	pid = fork();
	if (pid < 0)
		error("fork", 0);
	if (pid == 0)
	{
	cmd_table = make_cmd_table(cmd);	
	close_pipes(total_cmd, pipes, n_cmd);
	open_fds(cmd_table->redirections, &pipes[n_cmd][0], &pipes[n_cmd + 1][1], &have_outfile);
	dup2(pipes[n_cmd][0], STDIN_FILENO);
	if(n_cmd != (total_cmd - 1) || have_outfile)
		dup2(pipes[(n_cmd + 1)][1], STDOUT_FILENO);
	close(pipes[n_cmd][0]);
	close(pipes[(n_cmd + 1)][1]);
	exec_cmd(cmd_table->cmd_and_args);
	}
}

static void	await_all_children(int children_count) // , pid_t *cmd_pids)
{
	int	i;
	int	wstatus;
	int	waited_pid;
	i = -1;
	while (++i <= children_count)
		waited_pid = waitpid(-1, &wstatus, 0);
	return ;
}

void after_fork(int n_cmd, int **pipes)
{
	close_pipes_main(n_cmd, pipes);
	await_all_children(n_cmd);
	close(pipes[0][1]);
	close(pipes[n_cmd][0]);
}

static char	**convert_hash_arr(void)
{
	t_list	*aux;
	int	i;
	int len;
	char **environ;

	i = -1;
	len = 0;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			len++;
			aux = aux->next;
		}
	}
	environ = malloc(sizeof(char *) * len + 1);
	i = -1;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			environ[i] = ft_strjoin(((t_item *) aux->content)->key, "=");
			environ[i] = ft_strnjoin(environ[i],((t_item *) aux->content)->value, ft_strlen(((t_item *) aux->content)->value));
			aux = aux->next;
		}
	}
	return (environ);
}

void	exec_cmd(char **args)
{
	char		*cmd_path;
	t_list		*temp;
	char 		**environ;

	environ = convert_hash_arr();
	temp = find_entry("PATH", g_data->hash_table);
	if (*args[0] == '/' || *args[0] == '.' || *args[0] == '~')
		cmd_path = args[0];
	else
	{
		if (temp == NULL)
		{
			ft_putstr_fd("Error: path not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		cmd_path = get_path(&args[0], ((t_item *)temp->content)->value);
	}
	dprintf(2,"cmd 0 = %s in pid %d\n", cmd_path, getpid());
	execve(cmd_path, args, environ);
}

