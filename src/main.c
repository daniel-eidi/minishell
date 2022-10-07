/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:00:46 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 15:58:08 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*g_data;

static void	check_run_not_fork(char **cmd, int *i, t_pids_pipes *aux)
{
	t_cmd	*cmd_table;
	int		have_file;
	
	have_file = 0;
	cmd_table = make_cmd_table(*cmd);
	if (cmd_table->cmd_and_args)
	{
		if(is_builtin(cmd_table->cmd_and_args) == 2)
		{
			open_fds(cmd_table->redirections, aux, 0, &have_file);
			if (have_file > 1)
				dup2(aux->pipes[1][1], STDOUT_FILENO);
			free_split((void **)cmd);
			free(cmd);
			run_builtin(cmd_table, aux);
			*i = *i + 1;
		}
	}
	clear_cmd_table(cmd_table);
}

int looping(char *line, char **cwd)
{
	char		**cmd;
	int			i;
//	t_pids_pipes *aux;
	char		*s;

	signal_for_main();
	s = get_var_value("PWD");
	*cwd = ft_strjoin(s, "> ");
	line = readline(*cwd);
	free_ptr((void *)cwd);
	free_ptr((void *)&s);


	i = 0;
	while ((line[i] == ' ') || (line[i] == '\t'))
		i++;
	if (!line[i])
	{
		free(line);
		return (2);
	}

	if ( !line || ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return (0);
	}
	if(ft_strlen(line) > 0)
		add_history(line);
	cmd = token_line(line);
	before_fork(cmd, &g_data->aux);
	prepare_heredoc(cmd);
	i = -1;
	if (cmd[0] && !cmd[1])
		check_run_not_fork(cmd, &i, g_data->aux);
	while(cmd[++i] != NULL)	{
		fork_open_exec(cmd, i, g_data->aux);	}
	free_split((void **)cmd);
	after_fork(i, g_data->aux->pipes, g_data->aux->pids);
	free_ptr((void *)&g_data->aux);
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
	clear_data();
	exit_minishell(NULL, NULL);
	return(0);
}
