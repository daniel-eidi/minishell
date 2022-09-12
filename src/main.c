# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


int main(int argc, char **argv, char **envp)
{
	static char	*line;
	//char		**split;
	int			i;
	(void)	argv;
	(void)	argc;
	t_data	*data;
	line = "";

	data = init_data();
	hash_envp(data, envp);
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);
		// split = token_line(line);
		// ft_printf("envp \n");
		// while(envp[i])
		// 	ft_printf("%s\n", envp[i++]);
		// free_split((void *)split);
		// free(split);
	}
	return(0);
}
