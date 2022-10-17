/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:00:46 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/17 16:48:04 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>

t_data	*g_data;

static void	check_run_not_fork(char **cmd, int *i, t_pids_pipes *aux)
{
	t_cmd	*cmd_table;
	int		have_file;

	have_file = 0;
	cmd_table = make_cmd_table(*cmd);
	if (cmd_table->cmd_and_args)
	{
		if (is_builtin(cmd_table->cmd_and_args) == 2)
		{
			open_fds(cmd_table->redirections, aux, 0, &have_file);
			if (have_file > 1)
				dup2(aux->pipes[1][1], STDOUT_FILENO);
			run_builtin(cmd_table, aux);
			*i = *i + 1;
		}
	}
	clear_cmd_table(cmd_table);
}

int	read_and_check_line(char *line, char **cwd)
{
	char	*s;
	int		i;
	int		n;

	s = get_var_value("PWD");
	*cwd = ft_strjoin(s, "> ");
	line = readline(*cwd);
	free_ptr((void *)cwd);
	free_ptr((void *)&s);
	if (!line || ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return (0);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	i = 0;
	while ((line[i] == ' ') || (line[i] == '\t'))
		i++;
	if (line[i] == 0)
		n = 2;
	else
		n = 1;
	g_data->main_cmd = token_line(line);
	return (n);
}

void	free_main_cmd_and_aux(void)
{
	if ((g_data->main_cmd))
		free_split((void **)g_data->main_cmd);
	free_ptr((void *)&g_data->aux);
	free_ptr((void *)&g_data->main_cmd);
}

int	looping(char *line, char **cwd)
{
	int	i;

	signal_for_main();
	g_data->not_run = 0;
	i = read_and_check_line(line, cwd);
	if (!i)
		return (0);
	if ((g_data->main_cmd) && (i == 1))
	{
		before_fork(g_data->main_cmd, &g_data->aux);
		prepare_heredoc(g_data->main_cmd);
		if (!g_data->not_run)
		{
			i = -1;
			if (g_data->main_cmd[0] && !g_data->main_cmd[1])
				check_run_not_fork(g_data->main_cmd, &i, g_data->aux);
			while (g_data->main_cmd[++i] != NULL)
				fork_open_exec(g_data->main_cmd, i, g_data->aux);
		}
		after_fork(i, g_data->aux->pipes, g_data->aux->pids);
		if ((g_data->main_cmd[0]) && (!ft_strlen(g_data->main_cmd[0])))
			g_data->exit_code = 127;
	}
	free_main_cmd_and_aux();
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		*cwd;
	int			loop;

	(void) argv;
	(void) argc;
	loop = 1;
	g_data = init_data();
	hash_envp(g_data, envp);
	line = "";
	while (loop)
		loop = looping(line, &cwd);
	clear_data();
	exit_minishell(NULL, NULL);
	return (0);
}
