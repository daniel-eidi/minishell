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
	t_pids_pipes *aux;
	
	aux = NULL;
	//table_cmd = NULL;
	g_data = init_data();
	hash_envp(g_data, envp);
	// i = -1;
	// while (envp[++i])
	// 	printf("%s\n", envp[i]);
	line = "";
	cwd = ft_strjoin(get_var_value("PWD"), "> ");
	while(ft_strncmp(line = readline(cwd), "exit", 5))
	{
		if(ft_strlen(line) > 0)
			add_history(line);
		cmd = token_line(line);
		before_fork(cmd, &aux);
		//printf("total cmd = %d\n", total_cmd );
		i = -1;
		while(cmd[++i])
			fork_open_exec(cmd[i], i, aux);
		after_fork(i, aux->pipes, aux->pids);
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

// if (!ft_strcmp(cmd[0], "cd" ))
		// 	builtin_cd((t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd);
		// // if (!ft_strcmp(((t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd)->content, "env" ))
		// // 	builtin_env(g_data);
		// if (!ft_strcmp(cmd[0], "echo" ))
		// 	builtin_echo((t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd);
		// if (!ft_strcmp(cmd[0], "pwd" ))
		// builtin_pwd();
		// if (!ft_strcmp(cmd[0], "export" ))
		// 	builtin_export(((t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd));
		// if (!ft_strcmp(cmd[0], "env" ))		
		// 	builtin_env();
		// if (!ft_strcmp(cmd[0], "unset" ))		
		// 	builtin_unset(((t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd));