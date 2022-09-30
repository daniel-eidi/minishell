/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:00:46 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/30 15:24:30 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_data	*g_data;

static void	check_run_not_fork(char *cmd, int *i, t_pids_pipes *aux)
{
	t_cmd	*cmd_table;
	bool	have_outfile;
	
	printf ("aqui\n");
	have_outfile = false;
	cmd_table = make_cmd_table(cmd);
	if(is_builtin(cmd_table->cmd_and_args) == 2)
	{
		run_builtin(cmd_table->cmd_and_args);
		*i = *i + 2;	
	}	
	open_fds(cmd_table->redirections, &aux->pipes[0][0], \
	&aux->pipes[1][1], &have_outfile);
	dup2(aux->pipes[0][0], STDIN_FILENO);
	if (have_outfile)
		dup2(aux->pipes[1][1], STDOUT_FILENO);
	free_ptr((void **) aux->pipes);
	if(is_builtin(cmd_table->cmd_and_args) == 2)
	{
		run_builtin(cmd_table->cmd_and_args);
		*i = *i + 2;	
	}	
}

static void loop(char *line, char **cwd)
{
	char		**cmd;
	int			i;
	t_pids_pipes *aux;

	if(ft_strlen(line) > 0)
		add_history(line);
	cmd = token_line(line);
	before_fork(cmd, &aux);
	i = -1;
	if (!cmd[1])
		check_run_not_fork(cmd[0], &i, aux);
	printf("valor de i = %d\n", i);
	while(cmd[++i])
		fork_open_exec(cmd[i], i, aux);
	after_fork(i, aux->pipes, aux->pids);
	free_split((void *)cmd);
	free_ptr((void *)&cmd);
	free_ptr((void *)cwd);
	*cwd = ft_strjoin(get_var_value("PWD"), "> ");
}

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		*cwd;
	(void)	argv;
	(void)	argc;

	g_data = init_data();
	hash_envp(g_data, envp);
	line = "";
	cwd = ft_strjoin(get_var_value("PWD"), "> ");
	while(ft_strncmp(line = readline(cwd), "exit", 5))
	{
		loop(line, &cwd);
	}
	clear_table(g_data->hash_table);
	free_ptr((void *)&cwd);
	free(g_data);
	rl_clear_history();
	
	return(0);
}
