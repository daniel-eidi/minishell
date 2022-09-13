# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*data;

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	//char		**split;
	t_list	*teste;
	int			i;
	(void)	argv;
	(void)	argc;
	t_data	*data;
	line = "";

	data = init_data();
	hash_envp(data, envp);
	cmd_env(data);
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);

	}
	return(0);
}
