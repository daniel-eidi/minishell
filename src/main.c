/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:00:46 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/04 10:42:18 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*g_data;

static void	check_run_not_fork(char *cmd, int *i, t_pids_pipes *aux)
{
	t_cmd	*cmd_table;
	int		have_file;
	
	have_file = 0;
	cmd_table = make_cmd_table(cmd);
	if (cmd_table->cmd_and_args)
	{
		if(is_builtin(cmd_table->cmd_and_args) == 2)
		{
			dprintf(2, "aqui \n");
			open_fds(cmd_table->redirections, aux, 0, &have_file);
			if (have_file > 1)
				dup2(aux->pipes[1][1], STDOUT_FILENO);
			run_builtin(cmd_table->cmd_and_args);
			*i = *i + 1;
		}
	clear_cmd_table(cmd_table);
	}
}

int looping(char *line, char **cwd)
{
	char		**cmd;
	int			i;
	t_pids_pipes *aux;

	signal_for_main();
	*cwd = ft_strjoin(get_var_value("PWD"), "> ");
	line = readline(*cwd);
	free_ptr((void *)cwd);
	if ( !line || ft_strcmp(line, "exit") == 0)
		return (0);
	if(ft_strlen(line) > 0)
		add_history(line);
	cmd = token_line(line);
	before_fork(cmd, &aux);
	prepare_heredoc(cmd, aux);
	i = -1;
	if (cmd[0] && !cmd[1])
		check_run_not_fork(cmd[0], &i, aux);
	while(cmd[++i] != NULL)	{
		fork_open_exec(cmd[i], i, aux);	}
	after_fork(i, aux->pipes, aux->pids);
	free_ptr((void *)&aux);
	free_split((void **)cmd);
	free_ptr((void *)&cmd);
	return(1);
}

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		*cwd;
	int loop;
	(void)	argv;
	(void)	argc;
	
	loop = 1;
	g_data = init_data();
	hash_envp(g_data, envp);
	line = "";
	while(loop)
		loop = looping(line, &cwd);
	exit_minishell();
	return(0);
}

void exit_minishell(void)
{
	printf("exit\n");
	clear_table(g_data->hash_table);
	//free_ptr((void *)&cwd);
	free(g_data);
	rl_clear_history();
	exit (0);
}