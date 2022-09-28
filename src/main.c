# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*g_data;
int main(int argc, char **argv, char **envp)
{
	static char	*line;
//	char		*cmd;
//	char		*temp;
	char		*cwd;
	char		**cmd;
	int			i;
	(void)	argv;
	(void)	argc;
//	(void)	envp;
//	t_list **hash_table;
//	t_item	*item;
//	t_list	*aux;
//	t_list	**aux_cmd;
//	t_list	**aux_cmd1;
	// t_list	*aux2;
	// t_list	*aux3;
	// t_list	*aux4;
	//t_cmd  *table_cmd;
	int total_cmd;
	int **pipes;
	pid_t *pid;

	//table_cmd = NULL;
	g_data = init_data();
	hash_envp(g_data, envp);
	line = "";
	cwd = ft_strjoin(get_var_value("PWD"), "> ");
	while(ft_strncmp(line = readline(cwd), "exit", 5))
	{
		if(ft_strlen(line) > 0)
			add_history(line);
		cmd = token_line(line);
		before_fork(cmd, &total_cmd, &pipes, &pid);
		//printf("total cmd = %d\n", total_cmd );
		i = -1;
		while(cmd[++i])
			fork_open_exec(cmd[i], i, total_cmd, pipes, pid[i]);
		after_fork(i, pipes);
		//dprintf(2, "aqui \n");
		//clear_cmd_table(table_cmd);
		free_ptr((void *)&cmd);
		free_ptr((void *)&cwd);
		cwd = ft_strjoin(get_var_value("PWD"), "> ");
		//free(line);
	}
	printf("\n--------------\n");
	clear_table(g_data->hash_table);
	free_ptr((void *)&cwd);
	free(g_data);
	rl_clear_history();
	
	return(0);
}
