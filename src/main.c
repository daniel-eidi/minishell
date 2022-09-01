# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		*cmd;
	char		*temp;
	char		**split;
	int			i;
	(void)	argv;
	(void)	argc;
	(void)	envp;

	i=0;
	line = "";
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);
		temp = treat_arg(line);
		cmd = space_arg(temp, "<");
		ft_printf("comando com spaços - %s\n", cmd);
		split = ft_split(cmd, ' ');
		ft_printf("--	tentativa de tokens  --- \n");
		while(split[i])
			ft_printf("%s\n", split[i++]);
		free(line);
	}
	return(0);
}
