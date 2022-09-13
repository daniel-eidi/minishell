# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*data;

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		**token;
	(void)	argv;
	(void)	argc;
	t_data	*data;
	line = "";

	data = init_data();
	hash_envp(data, envp);
	cmd_env(data);
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		if(ft_strlen(line) > 0)
			add_history(line);
		token=token_line(line);
	}
	return(0);
}
